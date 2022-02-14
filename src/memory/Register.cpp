#include "Registers.h"

void Registers::incrementPc(unsigned char incr){
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

unsigned char Registers::getSP(){
    return this->sp;
}

unsigned char Registers::getPC(){
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