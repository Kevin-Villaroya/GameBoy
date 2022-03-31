#include <iostream>
#include <algorithm>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"

Gameboy::Gameboy(char* path) : memory(path), cpu(Processor(&memory)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;

	this->frequency = 4096;
	this->lastTimeFetch = 0;

	this->canTick = true;
	this->canSkip = false;
	this->waitingBreakingOpCode = false;
	this->isDebugMode = false;
	this->cpu.printMetadata();

	this->opCodeBreak.push_back(0xC8);
}

bool Gameboy::run(){
	uint32_t currentTime = 0;

	while(this->isRunning){
		currentTime = SDL_GetTicks();
		

		if(canTick){
			try{
				bool instructionExecuted = this->cpu.tick();

				this->updateTimers(instructionExecuted);
				this->debug(instructionExecuted);

				this->ppu.tick();
				this->treatEvent(currentTime);
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
		std::cout << "--tick--" << std::endl;

		if(isInstructionExecuted){
			if(this->waitingBreakingOpCode){
				if(std::find(this->opCodeBreak.begin(), this->opCodeBreak.end(), this->cpu.getInstruction()->opCode) != this->opCodeBreak.end()){
					this->waitingBreakingOpCode = false;

					this->cpu.dumpRegister();
				}
			}else{
				this->cpu.dumpRegister();
				this->canSkip = false;
			}
		}

		this->canTick = this->canSkip || this->waitingBreakingOpCode;
	}
}

Gameboy::~Gameboy(){
	delete this->view;
}