#include <iostream>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"

Gameboy::Gameboy(char* path) : cpu(Processor(path)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;
	this->canContinue = true;
	this->isDebugMode = false;
	this->cpu.printMetadata();
}

bool Gameboy::run(){
	while(this->isRunning){
		Event event = this->view->fetchEvent();
		this->treatEvent(event);

		if(this->canContinue){

			if(this->isDebugMode){
				std::cout << "tick" << std::endl;
				this->canContinue = false;
			}

			try{
				if(this->cpu.tick()){
					this->cpu.dump();
				}
			}catch(UnknownInstructionException &error){
				std::cerr << error.what() << std::endl;
				return 1;
			}
			
			this->ppu.tick();				
		}		
	}
	return 0;
}

void Gameboy::treatEvent(Event event){
	switch (event){
		case Event::QUIT:
			this->isRunning = false;
			break;
		
		case Event::TOUCH:
			this->canContinue = true;

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