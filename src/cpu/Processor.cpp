#include "Processor.h"
#include "InstructionFactory.h"
#include "startupException/StartupException.h"
#include <iostream>

Processor::Processor(char* path) : memory(path){
}

Instruction* Processor::fetch(){
    unsigned char instrByte = this->memory[this->registers.getPC()];

    Instruction* currentInstr = this->decodeAndLoad(instrByte);
    this->registers.incrementPc(currentInstr->getSize());

    return currentInstr;
}

Instruction* Processor::decodeAndLoad(unsigned char byteInstr){
    Instruction* instr = InstructionFactory::forCode(byteInstr);
    instr->setParameters(this->memory, this->registers.getPC() + 1);

    return instr;
}

void Processor::execute(Instruction& instr){
    instr.execute(this->memory, this->registers);
}

bool Processor::startupSequence(){
    //TODO
    return true;
}

const std::string Processor::getNameForCartridgeType(unsigned char type) {
	switch(type) {
		case 0x01:
			return "ROM+MBC1";
			
		case 0x02:
			return "ROM+MBC1+RAM";
			
		case 0x03:
			return "ROM+MBC1+RAM+BATTERY";
			
		case 0x05:
			return "ROM+MBC2";
			
		case 0x06:
			return "ROM+MBC2+BATTERY";
			
		case 0x08:
			return "ROM+RAM";
			
		case 0x09:
			return "ROM+RAM+BATTERY";
			
		case 0x0B:
			return "ROM+MMM01";
			
		case 0x0C:
			return "ROM+MMM01+SRAM";
			
		case 0x0D:
			return "ROM+MMM01+SRAM+BATTERY";
			
		case 0x12:
			return "ROM+MBC3+RAM";
			
		case 0x13:
			return "ROM+MBC3+RAM+BATTERY";
			
		case 0x19:
			return "ROM+MBC5";
			
		case 0x1A:
			return "ROM+MBC5+RAM";
			
		case 0x1B:
			return "ROM+MBC5+BATTERY";
			
		case 0x1C:
			return "ROM+MBC5+RUMBLE";
			
		case 0x1D:
			return "ROM+MBC5+RUMBLE+SRAM";
			
		case 0x1E:
			return "ROM+MBC5+RUMBLE+SRAM+BATTERY";
			
		case 0x1F:
			return "Pocket Camera";
			
		case 0xFD:
			return "Bandai TAMA5";
			
		case 0xFE:
			return "Hudson HuC-3";
			
		case 0x0F:
			return "ROM+MBC3+TIMER+BATTERY";
			
		case 0x10:
			return "ROM+MBC3+TIMER+RAM+BATTERY";
			
		case 0x11:
			return "ROM+MBC3";
			
		case 0xFF:
			return "HuDson HuC-1";
			
		default:
		case 0x00:
			return "ROM Only";
	}
}

void Processor::run(){
    bool canBoot = this->startupSequence();

    if(canBoot){
        this->memory.init();
        this->registers.init(this->memory);
        this->registers.setPC(0x100);

        while (true)
        {
            Instruction* instr = this->fetch();
            this->execute(*instr);
            //display

            delete instr;
        }
    }else{
        throw startupSequence();
    }  
}

void Processor::printMetadata() {
	std::string name;
	
	// Title memory range
	for(int i = 0x0134; i <= 0x0142; i++) {
		name += this->memory[i];	
	}
	
	unsigned char isColored = this->memory[0x0143];
	unsigned char isSGB = this->memory[0x0146];
	unsigned char cartridgeType = this->memory[0x0147];
	unsigned char localization = this->memory[0x014A];
	
	std::cout << name << " : " << std::endl;
	std::cout << " - Using color " << (isColored == this->memory[0x80] ? "True" : "False") << std::endl;
	std::cout << " - Using Super GameBoy functions : " << (isSGB == 0x03 ? "True" : "False") << std::endl;
	std::cout << " - Cartridge Type : " << this->getNameForCartridgeType(cartridgeType) << std::endl;
	std::cout << " - Localization : " << (localization == 0 ? "Japanese" : "Non-Japanese") << std::endl;
}
