#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "Memory.h"
#include <string>

enum class RegisterName{
    A,
    B,
    C,
    D,
    E,
    F,
    L,
    H
};

enum class DoubleRegisterName{
    AF,
    BC,
    DE,
    HL,
    PC,
    SP
};

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

    unsigned char flags;

    //Interrupt Master Enable Flag
    bool IME;

public:
    static std::string getRegisterName(RegisterName registerName);
    static std::string getDoubleRegisterName(DoubleRegisterName registerName);
    void init(Memory ram);

    void incrementPc(unsigned short);

    unsigned char getA() const;
    unsigned char getB() const;
    unsigned char getC() const;
    unsigned char getD() const;
    unsigned char getE() const;
    unsigned char getF() const;
    unsigned char getL() const;
    unsigned char getH() const;

    unsigned short getAF() const;
    unsigned short getBC() const;
    unsigned short getDE() const;
    unsigned short getHL() const;

    unsigned short getSP() const;
    unsigned short getPC() const;

    unsigned char getRegister(RegisterName) const;
    unsigned short getDoubleRegister(DoubleRegisterName) const;

    bool isFlagZ() const;
    bool isFlagN() const;
    bool isFlagH() const;
    bool isFlagC() const;

    void setFlagZ(bool value);
    void setFlagN(bool value);   
    void setFlagH(bool value);
    void setFlagC(bool value);

    void setAF(unsigned short af);
    void setBC(unsigned short bc);
    void setDE(unsigned short de);
    void setHL(unsigned short hl);

    void setRegister(RegisterName, unsigned char);
    void setDoubleRegister(DoubleRegisterName, unsigned short);

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

    void enbaleIME();
    void disableIME();

    bool isIME();

    std::string dump();
};

#endif
