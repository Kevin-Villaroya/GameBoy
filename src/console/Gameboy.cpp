#include <iostream>
#include "Gameboy.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"
#include "../display/Window.h"
#include "../display/Terminal.h"

Gameboy::Gameboy(char* path) : cpu(Processor(path)), view(new Window()), ppu(ProcessorGraphic(view, &cpu.getMemory())){
	this->isRunning = true;
	this->cpu.printMetadata();
}

bool Gameboy::run(){
	while(this->isRunning){
		Event event = this->view->fetchEvent();
		this->treatEvent(event);

		try{
	        this->cpu.tick();
	    }catch(UnknownInstructionException &error){
	        std::cerr << error.what() << std::endl;
	        return 1;
	    }
		
		this->ppu.tick();
	}
	return 0;
}

void Gameboy::treatEvent(Event event){
	switch (event){
		case Event::QUIT:
			this->isRunning = false;
			break;
		
		default:
			break;
	}
}

Gameboy::~Gameboy(){
	delete this->view;
}