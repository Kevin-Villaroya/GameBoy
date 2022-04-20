#include "Processor.h"
#include "InstructionFactory.h"
#include "startupException/StartupException.h"
#include "../util/DecToHex.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

Processor::Processor(Memory* memory, Registers* registers) : memory(memory), registers(registers){
	this->ticksDelayed = 0;
	this->instruction = nullptr;
}

Instruction* Processor::fetch(){
    Instruction* currentInstr = this->decodeAndLoad();
    this->registers->incrementPc(currentInstr->getSize());

    return currentInstr;
}

Instruction* Processor::decodeAndLoad(){
    Instruction* instr = InstructionFactory::forCode(*this->memory, this->registers->getPC());
    instr->setParameters(*this->memory, this->registers->getPC() + 1);

    return instr;
}

void Processor::execute(Instruction& instr){
    instr.execute(*this->memory, *this->registers);
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
			
		case 0x10:this->fetch();
		default:
		case 0x00:
			return "ROM Only";
	}
}

int Processor::tick(){
	if(this->ticksDelayed == 0){
		if(this->instruction != nullptr){
			delete this->instruction;
		}

		this->instruction = this->fetch();
	}

	this->ticksDelayed++;

	if(this->ticksDelayed >= this->instruction->getTiming()){
    	this->execute(*this->instruction);
    	this->ticksDelayed = 0;

		return this->instruction->getTiming();
	}

	return 0;
}

void Processor::printMetadata() {
	std::string name;
	
	// Title memory range
	for(int i = 0x0134; i <= 0x0142; i++) {
		name += this->memory->get(i);	
	}
	
	unsigned char isColored = this->memory->get(0x0143);
	unsigned char isSGB = this->memory->get(0x0146);
	unsigned char cartridgeType = this->memory->get(0x0147);
	unsigned char localization = this->memory->get(0x014A);
	
	std::cout << name << " : " << std::endl;
	std::cout << " - Using color " << (isColored == this->memory->get(0x80) ? "True" : "False") << std::endl;
	std::cout << " - Using Super GameBoy functions : " << (isSGB == 0x03 ? "True" : "False") << std::endl;
	std::cout << " - Cartridge Type : " << this->getNameForCartridgeType(cartridgeType) << std::endl;
	std::cout << " - Localization : " << (localization == 0 ? "Japanese" : "Non-Japanese") << std::endl;
}

void Processor::dumpRegister(){
	std::cout << this->instruction->toString() << std::endl;
	std::cout << "op code: " << shortToHex(this->instruction->opCode) << std::endl;

	std::cout << this->registers->dump() << std::endl;
	//std::cout << this->memory->dump() << std::endl;
}

void Processor::dumpRam(){
	std::cout << "==============ROM================" << std::endl;

	for(int i = 0; i < 0x3FFF; i++){
		if((i) % 16 == 0){
			std::cout << std::endl;
			std::cout <<shortToHex(i) + ": ";
		}
		
		std::cout <<"| " << charToHex(this->memory->get(i)) << " |";
	}
	std::cout << std::endl;

	std::cout << "==============ROM SWITCHABLE================" << std::endl;
	for(int i = 0x4000; i < 0x7FFF; i++){
		if((i - 0x4000) % 16 == 0){
			std::cout << std::endl;
			std::cout <<shortToHex(i) + ": ";
		}

		std::cout <<"| " << charToHex(this->memory->get(i)) << " |";
	}
	std::cout << std::endl;

	std::cout << "==============VIDEO RAM================" << std::endl;
	for(int i = 0X8000; i < 0x9FFF; i++){
		if((i - 0x8000) % 16 == 0){
			std::cout << std::endl;
			std::cout <<shortToHex(i) + ": ";
		}
		
		std::cout <<"| " << charToHex(this->memory->get(i)) << " |";
	}
	std::cout << std::endl;

	std::cout << "==============SPRITE ATTRIBUTES================" << std::endl;
	for(int i = 0XFE00; i < 0xFEA0; i++){
		if((i - 0x8000) % 16 == 0){
			std::cout << std::endl;
			std::cout <<shortToHex(i) + ": ";
		}
		
		std::cout <<"| " << charToHex(this->memory->get(i)) << " |";
	}
	std::cout << std::endl;

	std::cout << "==============ATTRIBUTES================" << std::endl;	
	std::cout <<"LY " << charToHex(this->memory->get(Memory::LY)) << std::endl;
	std::cout <<"LE " << charToHex(this->memory->get(Memory::IF)) << std::endl;
	std::cout <<"LF " << charToHex(this->memory->get(Memory::IE)) << std::endl;

}

Instruction* Processor::getInstruction(){
	return this->instruction;
}

Memory& Processor::getMemory(){
	return *this->memory;
}