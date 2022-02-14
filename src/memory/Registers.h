#ifndef __REGISTER_H__
#define __REGISTER_H__

class Registers {
public:
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

    void incrementPc(unsigned char);

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

    unsigned char getSP();
    unsigned char getPC();

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