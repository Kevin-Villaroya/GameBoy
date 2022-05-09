#include <iostream>
#include <algorithm>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../util/BitMath.h"
#include "../util/DecToHex.h"
#include <unistd.h>
#include <thread>
#include <unistd.h>

Gameboy::Gameboy(char* path) : memory(path), cpu(Processor(&memory, &registers)), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->running = true;
	this->paused = false;
	this->ticks = 0;
	this->memory.init(&this->oamDma);
	this->registers.init(&this->memory);
	this->registers.setPC(0x100);

	this->frequency = 4096;

	this->canTick = true;
	this->canSkip = false;
	this->waitingBreakingOpCode = false;
	this->isDebugMode = false;
	this->canContinue = false;
	this->die = false;
	this->cpu.printMetadata();
	this->view = new Window(&this->memory);
}

void Gameboy::launchCpuThread(){
	int n = 0;
    int stop = 0x10000;
	while(this->running && (n <= stop)){
		
		if(this->paused){
			SDL_Delay(10);
			continue;
		}
		
		int cpuTicks = this->cpu.step();;
		this->gameboyTick(cpuTicks);
		this->doInterrupts();

	}
	return;
}

bool Gameboy::run(){
	
	std::thread cpuThread(&Gameboy::launchCpuThread, this);

	uint64_t prevFrame = 0;
	while(!this->die){
		if(this->view->fetchEvent() == Event::QUIT)
			this->die = true;
		if(this->ppu.getCurrentFrame() != prevFrame){
			this->view->update(this->ppu.getVideoBuffer());
		}
		prevFrame = this->ppu.getCurrentFrame();
		
	}
	return 0;

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

	if(interruption == 4){
		std::cout << "doing interrupt " << interruption << std::endl;
	}
	

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

void Gameboy::treatEvent(){
	/*Event event = this->view->fetchEvent();

	switch (event){
		case Event::QUIT:
			this->running = false;
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
	}*/
}

void Gameboy::debugMode(){
	this->isDebugMode = true;
}

void Gameboy::debug(bool isInstructionExecuted){
	if(this->isDebugMode){

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

void Gameboy::gameboyTick(unsigned int nb){
	for(unsigned int i=0 ; i<(nb/4) ; i++){
		for(unsigned int j=0 ; j<4 ; j++){
			this->ticks++;
			this->cpu.timerTick();
			this->ppu.tick();
		}
		this->oamDma.dmaTick(&this->memory);
	}
}

Gameboy::~Gameboy(){
	delete this->view;
}

bool Gameboy::isRunning(){
	return running;
}

int Gameboy::getTicks(){
	return ticks;
}


bool Gameboy::isPaused(){
	return paused;
}