#include "Registers.h"
#include <iostream>

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

unsigned char Registers::getA(){
    return this->a;
}

unsigned char Registers::getB(){
    return this->b;
}

unsigned char Registers::getC(){
    return this->c;
}

unsigned char Registers::getD(){
    return this->d;
}

unsigned char Registers::getE(){
    return this->e;
}

unsigned char Registers::getF(){
    return this->f;
}

unsigned char Registers::getL(){
    return this->l;
}

unsigned char Registers::getH(){
    return this->h;
}

unsigned short Registers::getAF(){
    unsigned short af = this->getA();
    af = af << 8;
    af += this->getF();

    return af;
}

unsigned short Registers::getBC(){
    unsigned short bc = this->getB();
    bc = bc << 8;
    bc += this->getC();

    return bc;
}

unsigned short Registers::getDE(){
    unsigned short de = this->getD();
    de = de << 8;
    de += this->getE();

    return de;
}

unsigned short Registers::getHL(){
    unsigned short hl = this->getH();
    hl = hl << 8;
    hl += this->getL();

    return hl;
}

void Registers::setAF(unsigned short af){
    this->f = af;
    this->a = af >> 8;
}

void Registers::setBC(unsigned short bc){
    this->b = bc;
    this->c = bc >> 8;
}

void Registers::setDE(unsigned short de){
    this->d = de;
    this->e = de >> 8;
}

void Registers::setHL(unsigned short hl){
    this->h = hl;
    this->l = hl >> 8;
}

unsigned short Registers::getSP(){
    return this->sp;
}

unsigned short Registers::getPC(){
    return this->pc;
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