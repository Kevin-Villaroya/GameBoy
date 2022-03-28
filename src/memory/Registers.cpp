#include "Registers.h"
#include <iostream>
#include <stdexcept>

std::string Registers::getRegisterName(RegisterName registerName){
    switch(registerName){
        case RegisterName::A:
            return "A";
            break;
        case RegisterName::B:
            return "B";
            break;
        case RegisterName::C:
            return "C";
            break;
        case RegisterName::D:
            return "D";
            break;  
        case RegisterName::E:
            return "E";
            break;
        case RegisterName::F:
            return "F";
            break;
        case RegisterName::L:
            return "L";
            break;
        case RegisterName::H:
            return "H";
            break;
        default:
            return "";
            break;
    }
}

std::string Registers::getDoubleRegisterName(DoubleRegisterName registerName){
    switch(registerName){
        case DoubleRegisterName::AF:
            return "AF";
            break;
        case DoubleRegisterName::BC:
            return "BC";
            break;
        case DoubleRegisterName::DE:
            return "DE";
            break;
        case DoubleRegisterName::HL:
            return "HL";
            break;  
        case DoubleRegisterName::PC:
            return "PC";
            break;
        case DoubleRegisterName::SP:
            return "SP";
            break;
        default:
            return "";
            break;
    }
}

void Registers::init(Memory ram){
    this->setA(ram[0x01]);
    this->setF(ram[0xB0]);

    this->setB(ram[0x0013]);
    this->setC(ram[0x0014]);

    this->setD(ram[0x00D8]);
    this->setE(ram[0x00D9]);

    this->setH(ram[0x014D]);
    this->setL(ram[0x014E]);

    this->setSP(ram[0xFFFE]);
}

void Registers::incrementPc(unsigned short incr){
    this->pc += incr;
}

unsigned char Registers::getA() const{
    return this->a;
}

unsigned char Registers::getB() const{
    return this->b;
}

unsigned char Registers::getC() const{
    return this->c;
}

unsigned char Registers::getD() const{
    return this->d;
}

unsigned char Registers::getE() const{
    return this->e;
}

unsigned char Registers::getF() const{
    return this->f;
}

unsigned char Registers::getL() const{
    return this->l;
}

unsigned char Registers::getH() const{
    return this->h;
}

unsigned short Registers::getAF() const{
    unsigned short af = this->getA();
    af = af << 8;
    af |= this->getF();

    return af;
}

unsigned short Registers::getBC() const{
    unsigned short bc = this->getB();
    bc = bc << 8;
    bc |= this->getC();

    return bc;
}

unsigned short Registers::getDE() const{
    unsigned short de = this->getD();
    de = de << 8;
    de |= this->getE();

    return de;
}

unsigned short Registers::getHL() const{
    unsigned short hl = this->getH();
    hl = hl << 8;
    hl |= this->getL();

    return hl;
}

unsigned short Registers::getSP() const{
    return this->sp;
}

unsigned short Registers::getPC() const{
    return this->pc;
}

unsigned char Registers::getRegister(RegisterName registerName) const{
    switch (registerName){
    case RegisterName::A :
        return this->getA();
    case RegisterName::B :
        return this->getB();
    case RegisterName::C :
        return this->getC();
    case RegisterName::D :
        return this->getD();
    case RegisterName::E :
        return this->getE();
    case RegisterName::F :
        return this->getF();
    case RegisterName::L : 
        return this->getL();
    case RegisterName::H :
        return this->getH();
    default:
        throw std::runtime_error("Unknown register");
        break;
    }
}

unsigned short Registers::getDoubleRegister(DoubleRegisterName registerName) const{
    switch (registerName){
    case DoubleRegisterName::AF:
        return this->getAF();
    case DoubleRegisterName::BC:
        return this->getBC();
    case DoubleRegisterName::DE:
        return this->getDE();
    case DoubleRegisterName::HL:
        return this->getHL();
    case DoubleRegisterName::SP:
        return this->getSP();
    case DoubleRegisterName::PC:
        return this->getPC();
    default:
        throw std::runtime_error("Unknown double register");
    }
}

bool Registers::isFlagZ() const{
    return this->flags & 0b10000000;
}

bool Registers::isFlagN() const{
    return this->flags & 0b01000000;
}

bool Registers::isFlagH() const{
    return this->flags & 0b00100000;
}

bool Registers::isFlagC() const{
    return this->flags & 0b00010000;
}

void Registers::setFlagZ(bool value){
    if(value == true){
        this->flags = this->flags | 0b10000000;
    }else{
        this->flags = this->flags & 0b01111111;
    }
}

void Registers::setFlagN(bool value){
    if(value == true){
        this->flags = this->flags | 0b01000000;
    }else{
        this->flags = this->flags & 0b10111111;
    }
}

void Registers::setFlagH(bool value){
    if(value == true){
        this->flags = this->flags | 0b00100000;
    }else{
        this->flags = this->flags & 0b11011111;
    }
}

void Registers::setFlagC(bool value){
    if(value == true){
        this->flags = this->flags | 0b00010000;
    }else{
        this->flags = this->flags & 0b11101111;
    }
}

void Registers::setAF(unsigned short af){
    this->a = af >> 8;
    this->f = af;
}

void Registers::setBC(unsigned short bc){
    this->b = bc >> 8;
    this->c = bc;
}

void Registers::setDE(unsigned short de){
    this->d = de >> 8;
    this->e = de;
}

void Registers::setHL(unsigned short hl){
    this->h = hl >> 8;
    this->l = hl;
}

void Registers::setRegister(RegisterName registerName, unsigned char value){
    switch (registerName){
    case RegisterName::A :
        return this->setA(value);
    case RegisterName::B :
        return this->setB(value);
    case RegisterName::C :
        return this->setC(value);
    case RegisterName::D :
        return this->setD(value);
    case RegisterName::E :
        return this->setE(value);
    case RegisterName::F :
        return this->setF(value);
    case RegisterName::L : 
        return this->setL(value);
    case RegisterName::H :
        return this->setH(value);
    default:
        throw std::runtime_error("Unknown register");
    }
}

void Registers::setDoubleRegister(DoubleRegisterName registerName, unsigned short value){
    switch (registerName){
    case DoubleRegisterName::AF :
        return this->setAF(value);
    case DoubleRegisterName::BC :
        return this->setBC(value);
    case DoubleRegisterName::DE :
        return this->setDE(value);
    case DoubleRegisterName::HL :
        return this->setHL(value);
    case DoubleRegisterName::PC :
        return this->setPC(value);
    case DoubleRegisterName::SP :
        return this->setSP(value);
    default:
        throw std::runtime_error("Unknown double register");
    }
}

void Registers::setA(unsigned char a ){
    this->a = a;
}

void  Registers::setB(unsigned char b){
    this->b = b;
}

void Registers::setC(unsigned char c){
    this->c = c;
}

void Registers::setD(unsigned char d){
    this->d = d;
}

void Registers::setE(unsigned char e){
    this->e = e;
}

void Registers::setF(unsigned char f){
    this->f = f;
}

void Registers::setL(unsigned char l){
    this->l = l;
}

void Registers::setH(unsigned char h){
    this->h = h;
}

void Registers::setSP(unsigned short sp){
    this->sp = sp;
}

void Registers::setPC(unsigned short pc){
    this->pc = pc;
}

void Registers::enbaleIME(){
    this->IME = true;
}

void Registers::disableIME(){
    this->IME = false;
}

bool Registers::isIME(){
    return this->IME;
}

std::string Registers::dump(){
    char pc[5];
    char sp[5];

	sprintf(pc, "%04X", this->getPC());
    sprintf(sp, "%04X", this->getSP());

    return "PC: " + std::string(pc) + " SP: " + std::string(sp); 
}