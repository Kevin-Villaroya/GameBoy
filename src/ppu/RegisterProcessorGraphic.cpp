#include "RegisterProcessorGraphic.h"

RegisterProcessorGraphic::RegisterProcessorGraphic(Memory* ram) : ram(ram){}

unsigned char RegisterProcessorGraphic::getLY(){
    return ram->get(0xff44);
}

void RegisterProcessorGraphic::setLY(unsigned char value){
    ram->set(0xFF44, value);
}

unsigned char RegisterProcessorGraphic::getLCDC(){
    return ram->get(0xff40);
}

void RegisterProcessorGraphic::setLCDC(unsigned char value){
    ram->set(0xff40, value);
}

unsigned char RegisterProcessorGraphic::getBGP(){
    return ram->get(0xff47);
}

void RegisterProcessorGraphic::setBGP(unsigned char value){
    ram->set(0xff47, value);
}

unsigned char RegisterProcessorGraphic::getSCY(){
    return ram->get(0xff42);
}

void RegisterProcessorGraphic::setSCY(unsigned char value){
    ram->set(0xff42, value);
}

unsigned char RegisterProcessorGraphic::getSCX(){
	return ram->get(0xff43);
}

void RegisterProcessorGraphic::setSCX(unsigned char value){
	ram->set(0xff43, value);
}

unsigned char RegisterProcessorGraphic::getWY(){
	return ram->get(0xff4A);
}

void RegisterProcessorGraphic::setWY(unsigned char value){
	ram->set(0xff4A, value);
}

unsigned char RegisterProcessorGraphic::getWX(){
	return ram->get(0xff4B);
}

void RegisterProcessorGraphic::setWX(unsigned char value){
	ram->set(0xff4B, value);
}