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