#include <iostream>
#include <algorithm>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"
#include "../util/BitMath.h"

Gameboy::Gameboy(char* path) : memory(path), cpu(Processor(&memory, &registers)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;

	this->memory.init();
	this->registers.init(&this->memory);
	this->registers.setPC(0x000);

	this->frequency = 4096;
	this->lastTimeFetch = 0;

	this->canTick = true;
	this->canSkip = false;
	this->waitingBreakingOpCode = false;
	this->isDebugMode = false;
	this->canContinue = false;
	this->cpu.printMetadata();

	this->pcValueBreak.push_back(0x02CD);
	this->pcValueBreak.push_back(0x29BA);
}

bool Gameboy::run(){
	uint32_t currentTime = 0;

	while(this->isRunning){
		currentTime = SDL_GetTicks();
		
		this->treatEvent(currentTime);

		if(canTick){
			try{
				bool instructionExecuted = this->cpu.tick();

				this->updateTimers(instructionExecuted);
				this->debug(instructionExecuted);
				this->ppu.tick();
				this->doInterrupts();

			}catch(UnknownInstructionException &error){
				std::cerr << error.what() << std::endl;
				return 1;
			}			
		}	
	}
	return 0;
}

void Gameboy::updateTimers(bool instructionExecuted){
	if(instructionExecuted){
		this->memory.updateTimers(this->cpu.getInstruction()->getTiming());
	}
}

void Gameboy::doInterrupts(){
	if(this->registers.isIME()){
		unsigned char requests = this->memory.get(Memory::IF);
		unsigned char enabled = this->memory.get(Memory::IE);

		if(requests > 0){
			for(int i = 0; i < 5; i++){
				if(testBit(requests,i)){
					if(testBit(enabled, i)){
						this->serviceInterrupt(i);
					}
				}
			}
		}
	}
}

void Gameboy::serviceInterrupt(int interruption){
	this->registers.disableIME();

	unsigned char requests = this->memory.get(Memory::IF);
	resetBit(requests, interruption);
	this->memory.set(Memory::IF, requests);

	// push pc in the stack
	unsigned short sp = registers.getSP();
	unsigned short pc = registers.getPC();
	
	this->memory.writeMemory(sp - 1, pc >> 8);
	this->memory.writeMemory(sp - 2, pc);
	
	registers.setSP(sp-2);

	//call a interrupt-service routine
	switch (interruption){
		case 0:
			this->registers.setPC(0x40);
			break;
		case 1:
			this->registers.setPC(0x48);
			break;
		case 2:
			this->registers.setPC(0x50);
			break;
		case 4:
			this->registers.setPC(0x60);
			break;
		
		default:
			break;
	}
}

void Gameboy::treatEvent(uint32_t currentTime){
	if(this->lastTimeFetch + Gameboy::DELAY_FETCH <= currentTime){
		Event event = this->view->fetchEvent();
		this->lastTimeFetch = currentTime;

		switch (event){
			case Event::QUIT:
				this->isRunning = false;
				break;
			
			case Event::TICK:
				this->canTick = true;
				break;
			case Event::SKIP:
				this->canSkip = true;
				this->canTick = true;
				break;
			case Event::WAIT_OPCODE_BREAKER:
				this->waitingBreakingOpCode = true;
				this->canTick = true;
				break;
			case Event::DUMP_RAM:
				this->cpu.dumpRam();
				break;
			case Event::CONTINUE:
				this->canContinue = !this->canContinue;
				this->canTick = true;
				break;
			case Event::A:
				this->gameboyKey(4);
				break;
			case Event::S:
				this->gameboyKey(5);
				break;
			case Event::RETURN:
				this->gameboyKey(7);
				break;
			case Event::SPACE:
				this->gameboyKey(6);
				break;
			case Event::RIGHT:
				this->gameboyKey(0);
				break;
			case Event::LEFT:
				this->gameboyKey(1);
				break;
			case Event::UP:
				this->gameboyKey(2);
				break;
			case Event::DOWN:
				this->gameboyKey(3);
				break;
			default:
				break;
		}
	}
}

void Gameboy::debugMode(){
	this->isDebugMode = true;
}

void Gameboy::debug(bool isInstructionExecuted){
	if(this->isDebugMode){
		//std::cout << "--tick--" << std::endl;

		if(isInstructionExecuted){
			if(this->waitingBreakingOpCode){
				if(this->needBreak()){
					this->waitingBreakingOpCode = false;

					this->cpu.dumpRegister();
				}
			}else{
				this->cpu.dumpRegister();
				this->canSkip = false;
			}
		}

		this->canTick = this->canSkip || this->waitingBreakingOpCode || this->canContinue;
	}
}

bool Gameboy::needBreak(){
	bool opCodeBreak = std::find(this->opCodeBreak.begin(), this->opCodeBreak.end(), this->cpu.getInstruction()->opCode) != this->opCodeBreak.end();
	bool pcCodeBreak = std::find(this->pcValueBreak.begin(), this->pcValueBreak.end(), this->registers.getPC()) != this->pcValueBreak.end();
	
	return opCodeBreak || pcCodeBreak;
}

void Gameboy::gameboyKey(int key){
	bool previouslyUnset = false;

	if(testBit(this->memory.getJoypad(), key) == false){
		previouslyUnset = true;
	}

	this->memory.setJoypad(returnResetBit(this->memory.getJoypad(), key));

	bool buttonPressed = true;

	if(key < 3){
		buttonPressed = false;
	}

	unsigned char keyRequest = this->memory.get(Memory::JOYPAD);
	bool requestInterrupt = false;

	if(buttonPressed && !testBit(keyRequest, 5)){
		requestInterrupt = true;
	}else if(!buttonPressed && !testBit(keyRequest, 4)){
		requestInterrupt = true;
	}

	if(requestInterrupt && !previouslyUnset){
		this->memory.requestInterupt(4);
	}
}

Gameboy::~Gameboy(){
	delete this->view;
}