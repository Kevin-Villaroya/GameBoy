#include <iostream>
#include <algorithm>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"

Gameboy::Gameboy(char* path) : cpu(Processor(path)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;
	this->canTick = true;
	this->canSkip = false;
	this->waitingBreakingOpCode = false;
	this->isDebugMode = false;
	this->cpu.printMetadata();

	this->opCodeBreak.push_back(192);
}

bool Gameboy::run(){
	uint32_t delay = 0;
	while(this->isRunning){

		if(delay + 20 <= SDL_GetTicks()){
			Event event = this->view->fetchEvent();
			this->treatEvent(event);
			delay = SDL_GetTicks();
		}

		if(canTick){
			try{
				bool instructionExecuted = this->cpu.tick();

				if(this->isDebugMode){
					std::cout << "--tick--" << std::endl;

					if(instructionExecuted){
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

				this->ppu.tick();
			}catch(UnknownInstructionException &error){
				std::cerr << error.what() << std::endl;
				return 1;
			}			
		}	
	}
	return 0;
}

void Gameboy::treatEvent(Event event){
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

void Gameboy::debugMode(){
	this->isDebugMode = true;
}

Gameboy::~Gameboy(){
	delete this->view;
}