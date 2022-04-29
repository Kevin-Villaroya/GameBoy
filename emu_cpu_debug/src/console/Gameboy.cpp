#include <iostream>
#include <algorithm>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"
#include "../util/BitMath.h"
#include "../util/DecToHex.h"
#include <unistd.h>

Gameboy::Gameboy(char* path) : memory(path), cpu(Processor(&memory, &registers)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;
	this->paused = false;
	this->ticks = 0;

	this->memory.init();
	this->registers.init(&this->memory);
	this->registers.setPC(0x100);

	this->frequency = 4096;	
	this->lastTimeFetch = 0;

	this->canTick = true;
	this->canSkip = false;
	this->waitingBreakingOpCode = false;
	this->isDebugMode = false;
	this->canContinue = false;
	this->die = false;
	this->cpu.printMetadata();

	//this->opCodeBreak.push_back(0x10);
	this->pcValueBreak.push_back(0x0358);
	//this->pcValueBreak.push_back(0x29BA);
}

bool Gameboy::run(){
	int n = 0;
    int stop = 0x150000;
	int x = 0;
	while(this->isRunning && (n <= stop)){
		//printf("0X80: %04X 0x81: %04X 0x82: %04X 0x83: %04X\n", this->memory.get(0xFF80), this->memory.get(0xFF81), this->memory.get(0xFF82), this->memory.get(0xFF83));
		//printf("SP = %04X\n", this->registers.getSP());

		//if(this->cpu.isHalt()) x ++;
		//if(!this->cpu.isHalt() && x>0){printf("Number of hlat : %04X", x);exit(0);}
		//printf("0XFF0F = %02X TIMA = %02X TAC = %02X\n", this->memory.get(0xFF0F), this->memory.get(0xFF05), this->memory.get(0xFF07));
		/*
		if(n == 0x2da56 || n == 0x2da57){
		printf("SP = %04X\n", this->registers.getSP());
		for(int i = 0xDFFE ; i>=0xDFF0 ; i--)
			printf("[%04X] = %02X\n", i, this->memory.get(i));
		

		}
		*/
		

		if(this->paused){
			SDL_Delay(10);
			continue;
		}
		printf("%08x %08lX - ",n ,this->ticks);
		int cpuTicks = 0;
		if((cpuTicks = this->cpu.step()) != -1){
			
		}
		this->gameboyTick(cpuTicks);
		

	}

	while(!this->die){
		sleep(1000);
		this->view->fetchEvent();
	}

	/*
	uint32_t currentTime = 0;

	while(this->isRunning){
		currentTime = SDL_GetTicks();
		
		this->treatEvent(currentTime);

		if(canTick){
			try{
				this->doInterrupts();

				if(!this->registers.isHalt()){
					bool instructionExecuted = this->cpu.tick();
					this->updateTimers(instructionExecuted);
					this->debug(instructionExecuted);
				}

				this->ppu.tick();
			}catch(UnknownInstructionException &error){
				std::cerr << error.what() << std::endl;
				return 1;
			}			
		}		
	}
	*/

	
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

		if(testBit(requests, 0)){
			//std::cout << charToHex(enabled) << std::endl;
			//std::cout << shortToHex(this->registers.getPC()) << std::endl;
		}

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
	this->registers.resetHalt();
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

	//std::cout << "doing interrupt " << interruption << std::endl;

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
				if(this->isDebugMode){
					this->cpu.dumpRam();
				}
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

void Gameboy::gameboyTick(unsigned int nb){
	for(unsigned int i=0 ; i<nb ; i++){
		this->ticks++;
		this->cpu.timerTick();
	}
}

Gameboy::~Gameboy(){
	delete this->view;
}