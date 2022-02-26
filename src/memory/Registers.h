#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "Memory.h"

class Registers {
private:
    //registers in cpu
	unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    unsigned char f;
    unsigned char l;
    unsigned char h;

    //registers pointer
	unsigned short sp;
	unsigned short pc;

public:
    void init(Memory ram);

    void incrementPc(unsigned short);

    unsigned char getA();
    unsigned char getB();
    unsigned char getC();
    unsigned char getD();
    unsigned char getE();
    unsigned char getF();
    unsigned char getL();
    unsigned char getH();

    unsigned short getAF();
    unsigned short getBC();
    unsigned short getDE();
    unsigned short getHL();

    void setAF(unsigned short af);
    void setBC(unsigned short bc);
    void setDE(unsigned short de);
    void setHL(unsigned short hl);

    unsigned short getSP();
    unsigned short getPC();

    void setA(unsigned char);
    void setB(unsigned char);
    void setC(unsigned char);
    void setD(unsigned char);
    void setE(unsigned char);
    void setF(unsigned char);
    void setL(unsigned char);
    void setH(unsigned char);

    void setSP(unsigned short);
    void setPC(unsigned short);
};

#endif