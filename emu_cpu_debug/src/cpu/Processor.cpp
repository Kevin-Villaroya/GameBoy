#include "Processor.h"
#include "InstructionFactory.h"
#include "startupException/StartupException.h"
#include "../util/DecToHex.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#define INTERRUPT_ENABLE 0xFFFF
#define INTERRUPT_FLAGS 0xFF0F
#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07 

Processor::Processor(Memory* memory, Registers* registers) : memory(memory), registers(registers){
	this->ticksDelayed = 0;
	this->instruction = nullptr;
	this->halted = false;
	this->interruptMasterEnable = false;
	this->enableIME = false;
}

Instruction* Processor::fetch(){
    Instruction* currentInstr = this->decodeAndLoad();

    return currentInstr;
}

Instruction* Processor::decodeAndLoad(){
    Instruction* instr = InstructionFactory::forCode(this, *this->memory, this->registers->getPC());
    instr->setParameters(*this->memory, this->registers->getPC() + 1);

    return instr;
}

void Processor::execute(Instruction& instr){
    instr.execute(*this->memory, *this->registers);
}

int Processor::step(){
	int cpuTicks = this->memory->get(this->registers->getPC()) == 0xCB ? 4 : 0;
	if(!this->halted){
		if(this->instruction != nullptr){
			delete this->instruction;
		}

		this->instruction = this->fetch();
		this->printRegisters();
		this->registers->incrementPc(this->instruction->getSize());
		
		
		this->dbgUpdate();
		this->dbgPrint();
		
		
		
		
		this->execute(*this->instruction);
		cpuTicks += this->instruction->getTiming();
	}
	else{
		cpuTicks = 4;
		if(this->memory->get(INTERRUPT_FLAGS)){
			this->halted = false;
		}
	}

	if(this->interruptMasterEnable){
		this->doInterrupt();
		this->enableIME = false;
	}

	if(this->enableIME){
		this->interruptMasterEnable = true;
	}

	return cpuTicks;// à voir pour le timing
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

void Processor::printRegisters(){
	printf("%04X: ", this->registers->getPC());
	std::cout<<this->instruction->toString();
	int offSet = 15 - this->instruction->toString().size();
	while(offSet-- > 0) printf(" ");
	printf("(%02X %02X %02X)",
		this->memory->get(this->registers->getPC()),
		this->memory->get(this->registers->getPC()+1),
		this->memory->get(this->registers->getPC()+2));
	printf(" A: %02X F: %c%c%c%c BC: %02X%02X DE: %02X%02X HL: %02X%02X\n", 
		this->registers->getA(), 
		this->registers->isFlagZ() ? 'Z' : '-', this->registers->isFlagN() ? 'N' : '-', this->registers->isFlagH() ? 'H' : '-', this->registers->isFlagC() ? 'C' : '-',
		this->registers->getB(), this->registers->getC(),
		this->registers->getD(), this->registers->getE(),
		this->registers->getH(), this->registers->getL());
}

Instruction* Processor::getInstruction(){
	return this->instruction;
}

Memory& Processor::getMemory(){
	return *this->memory;
}

void Processor::dbgUpdate(){
	if(this->memory->get(0xFF02) == 0x81){
		char c = this->memory->get(0xFF01);
		this->dbgMsg[this->dbgMsgSize++] = c;
		this->memory->set(0xFF02, 0);
	}
}

void Processor::dbgPrint(){
	if(this->dbgMsg[0]){
		printf("DBG : %s\n", this->dbgMsg);
	}
}

void Processor::setIME(bool b){
	this->interruptMasterEnable = b;
}

void Processor::setEnableIME(bool b){
	this->enableIME = b;
}

void Processor::setHalt(bool b){
	this->halted = b;
}

void Processor::interruptHandle(unsigned short address){
	unsigned char loPC = this->registers->getPC();
	unsigned char hiPC = this->registers->getPC()>>8;
	unsigned short sp = this->registers->getSP();

	this->memory->set(sp-1, hiPC);
	this->memory->set(sp-2, loPC);
	this->registers->setSP(sp-2);
	this->registers->setPC(address);
}	

bool Processor::interruptCheck(unsigned short address,int interruptType){
	unsigned char interruptFlags = this->memory->get(INTERRUPT_FLAGS);
	unsigned char interruptEnable = this->memory->get(INTERRUPT_ENABLE);

	if( (interruptFlags & (unsigned char)interruptType)  && (interruptEnable & (unsigned char)interruptType)){
		//printf("triggered\n");
		this->interruptHandle(address);

		interruptFlags &= ~(unsigned char)interruptType;
		this->memory->set(INTERRUPT_FLAGS, interruptFlags);
		this->halted = false;
		this->interruptMasterEnable = false;

		return true;
	}
	return false;
}

void Processor::doInterrupt(){
	if(this->interruptCheck(0x40, IT_VBLANK)){

	}
	else if(this->interruptCheck(0x48, IT_LCD_STAT)){

	}
	else if(this->interruptCheck(0x50, IT_TIMER)){
		
	}
	else if(this->interruptCheck(0x58, IT_SERIAL)){
		
	}
	else if(this->interruptCheck(0x60, IT_JOYPAD)){
		
	}
}

void Processor::timerTick(){
	unsigned char tacValue = this->memory->get(TAC);

	unsigned short divValue = this->memory->get(DIV)<<8;
	divValue += this->memory->getDividerClock();
	this->memory->incDividerClock();
	unsigned short ndivValue = divValue + 1;

	bool timaIncr;

	switch(tacValue & 0b11){
		case 0b00:
			timaIncr = (ndivValue & (1<<9)) && !(divValue & (1<<9));
			break;
		case 0b01:
			timaIncr = (ndivValue & (1<<3)) && !(divValue & (1<<3));
			break;
		case 0b10:
			timaIncr = (ndivValue & (1<<5)) && !(divValue & (1<<5));
			break;
		case 0b11:
			timaIncr = (ndivValue & (1<<7)) && !(divValue & (1<<7));
			break;
	}

	if(timaIncr && (tacValue & (0b100))){
		unsigned char tima;
		unsigned char tma = this->memory->get(TMA);
		this->memory->set(TIMA, tima = this->memory->get(TIMA)+1);
		
		if(tima == 0xFF){
			this->memory->set(TIMA, tma);
			
			//interrupt request
			unsigned char interruptFlags = this->memory->get(INTERRUPT_FLAGS);
			this->memory->set(INTERRUPT_FLAGS, interruptFlags|IT_TIMER);
		}
	}

}

bool Processor::isHalt(){
	return this->halted;
}


