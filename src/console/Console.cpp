#include <iostream>
#include "Console.h"
#include "../cpu/instruction/instructionError/UnknownInstructionException.h"

Console::Console(char* path) : cpu(Processor(path)), ppu(ProcessorGraphic()){
	this->cpu.printMetadata();
}

bool Console::run(){
	while(true){
		try{
	        this->cpu.tick();
	    }catch(UnknownInstructionException &error){
	        std::cerr << error.what() << std::endl;
	        return 1;
	    }
		
		this->ppu.tick();
	}
}