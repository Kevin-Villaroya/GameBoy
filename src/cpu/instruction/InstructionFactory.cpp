#include "InstructionFactory.h"
#include "instructionError/UnknownInstructionException.h"

#include "opcode/jmp/JumpUnconditionalImmediate.h"
#include "opcode/nop/Nop.h"
#include "opcode/inc/IncrementRegister.h"
#include "opcode/load/LoadRegisterToRegister.h"
#include "opcode/load/LoadImmediateToDoubleRegister.h"
#include "opcode/push/PushDoubleRegisterToStack.h"
#include "opcode/pop/PopStackToDoubleRegister.h"
#include "opcode/add/AddRegisterToA.h"
#include "opcode/add/AddImmediateToA.h"
#include "opcode/add/AddDoubleRegisterToA.h"
#include "opcode/add/AddCarryRegisterToA.h"
#include "opcode/add/AddCarryDoubleRegisterToA.h"
#include "opcode/add/AddCarryImmediateToA.h"
#include "opcode/sub/SubRegisterToA.h"
#include "opcode/sub/SubDoubleRegisterToA.h"
#include "opcode/sub/SubImmediateToA.h"
#include "opcode/sub/SubCarryRegisterToA.h"
#include "opcode/sub/SubCarryDoubleRegisterToA.h"
#include "opcode/sub/SubCarryImmediateToA.h"
#include "opcode/and/AndRegisterToA.h"
#include "opcode/and/AndDoubleRegisterToA.h"
#include "opcode/and/AndImmediateToA.h"
#include "opcode/or/OrRegisterToA.h"
#include "opcode/or/OrDoubleRegisterToA.h"
#include "opcode/or/OrImmediateToA.h"
#include "opcode/xor/XorRegisterToA.h"
#include "opcode/xor/XorDoubleRegisterToA.h"
#include "opcode/xor/XorImmediateToA.h"
#include "opcode/cp/CpRegisterToA.h"
#include "opcode/cp/CpDoubleRegisterToA.h"
#include "opcode/cp/CpImmediateToA.h"

Instruction* InstructionFactory::forCode(unsigned char byteInstr){
    switch(byteInstr){
        case 0xc3:
            return new JumpUnconditionalImmediate();
        case 0x00:
            return new Nop();
        case 0x2c:
            return new IncrementRegister(RegisterName::L);
        case 0x04:
            return new IncrementRegister(RegisterName::B);
        case 0x14:
            return new IncrementRegister(RegisterName::D);
        case 0x24:
            return new IncrementRegister(RegisterName::H);
        case 0x0c:
            return new IncrementRegister(RegisterName::C);
        case 0x1c:
            return new IncrementRegister(RegisterName::E);
        case 0x3c:
            return new IncrementRegister(RegisterName::A);
        case 0x40:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::B);
        case 0x50:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::B);
        case 0x60:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::B);
        case 0x41:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::C);
        case 0x51:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::C);
        case 0x61:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::C);
        case 0x42:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::D);
        case 0x52:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::D);
        case 0x62:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::D);
        case 0x43:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::E);
        case 0x53:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::E);
        case 0x63:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::E);
        case 0x44:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::H);
        case 0x54:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::H);
        case 0x64:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::H);
        case 0x45:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::L);
        case 0x55:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::L);
        case 0x65:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::L);
        case 0x47:
            return new LoadRegisterToRegister(RegisterName::B, RegisterName::A);
        case 0x57:
            return new LoadRegisterToRegister(RegisterName::D, RegisterName::A);
        case 0x67:
            return new LoadRegisterToRegister(RegisterName::H, RegisterName::A);
        case 0x48:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::B);
        case 0x58:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::B);
        case 0x68:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::B);
        case 0x78:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::B);
        case 0x49:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::C);
        case 0x59:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::C);
        case 0x69:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::C);
        case 0x79:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::C);
        case 0x4A:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::D);
        case 0x5A:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::D);
        case 0x6A:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::D);
        case 0x7A:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::D);
        case 0x4B:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::E);
        case 0x5B:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::E);
        case 0x6B:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::E);
        case 0x7B:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::E);
        case 0x4C:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::H);
        case 0x5C:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::H);
        case 0x6C:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::H);
        case 0x7C:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::H);
        case 0x4D:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::L);
        case 0x5D:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::L);
        case 0x6D:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::L);
        case 0x7D:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::L);
        case 0x4F:
            return new LoadRegisterToRegister(RegisterName::C, RegisterName::A);
        case 0x5F:
            return new LoadRegisterToRegister(RegisterName::E, RegisterName::A);
        case 0x6F:
            return new LoadRegisterToRegister(RegisterName::L, RegisterName::A);
        case 0x7F:
            return new LoadRegisterToRegister(RegisterName::A, RegisterName::A);
        case 0x01:
            return new LoadImmediateToDoubleRegister(DoubleRegisterName::BC);
        case 0x11:
            return new LoadImmediateToDoubleRegister(DoubleRegisterName::DE);
        case 0x21:
            return new LoadImmediateToDoubleRegister(DoubleRegisterName::HL);
        case 0x31:
            return new LoadImmediateToDoubleRegister(DoubleRegisterName::SP);
        case 0xF5:
            return new PushDoubleRegisterToStack(DoubleRegisterName::AF);
        case 0xC5:
            return new PushDoubleRegisterToStack(DoubleRegisterName::BC);
        case 0xD5:
            return new PushDoubleRegisterToStack(DoubleRegisterName::DE);
        case 0xE5:
            return new PushDoubleRegisterToStack(DoubleRegisterName::HL);
        case 0xF1:
            return new PopStackToDoubleRegister(DoubleRegisterName::AF);
        case 0xC1:
            return new PopStackToDoubleRegister(DoubleRegisterName::BC);
        case 0xD1:
            return new PopStackToDoubleRegister(DoubleRegisterName::DE);
        case 0xE1:
            return new PopStackToDoubleRegister(DoubleRegisterName::HL);
        case 0x87:
            return new AddRegisterToA(RegisterName::A);
        case 0x80:
            return new AddRegisterToA(RegisterName::B);
        case 0x81:
            return new AddRegisterToA(RegisterName::C);
        case 0x82:
            return new AddRegisterToA(RegisterName::D);
        case 0x83:
            return new AddRegisterToA(RegisterName::E);
        case 0x84:
            return new AddRegisterToA(RegisterName::H);
        case 0x85:
            return new AddRegisterToA(RegisterName::L);
        case 0x86:
            return new AddDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xC6:
            return new AddImmediateToA();
        case 0x8F:
            return new AddCarryRegisterToA(RegisterName::A);
        case 0x88:
            return new AddCarryRegisterToA(RegisterName::B);
        case 0x89:
            return new AddCarryRegisterToA(RegisterName::C);
        case 0x8A:
            return new AddCarryRegisterToA(RegisterName::D);
        case 0x8B:
            return new AddCarryRegisterToA(RegisterName::E);
        case 0x8C:
            return new AddCarryRegisterToA(RegisterName::H);
        case 0x8D:
            return new AddCarryRegisterToA(RegisterName::L);
        case 0x8E:
            return new AddCarryDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xCE:
            return new AddCarryImmediateToA();
        case 0x97:
            return new SubRegisterToA(RegisterName::A);
        case 0x90:
            return new SubRegisterToA(RegisterName::B);
        case 0x91:
            return new SubRegisterToA(RegisterName::C);
        case 0x92:
            return new SubRegisterToA(RegisterName::D);
        case 0x93:
            return new SubRegisterToA(RegisterName::E);
        case 0x94:
            return new SubRegisterToA(RegisterName::H);
        case 0x95:
            return new SubRegisterToA(RegisterName::L);
        case 0x96:
            return new SubDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xD6:
            return new SubImmediateToA();
        case 0x9F:
            return new SubCarryRegisterToA(RegisterName::A);
        case 0x98:
            return new SubCarryRegisterToA(RegisterName::B);
        case 0x99:
            return new SubCarryRegisterToA(RegisterName::C);
        case 0x9A:
            return new SubCarryRegisterToA(RegisterName::D);
        case 0x9B:
            return new SubCarryRegisterToA(RegisterName::E);
        case 0x9C:
            return new SubCarryRegisterToA(RegisterName::H);
        case 0x9D:
            return new SubCarryRegisterToA(RegisterName::L);    
        case 0x9E:
            return new SubCarryDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xDE:
            return new SubCarryImmediateToA();
        case 0xA7:
            return new AndRegisterToA(RegisterName::A);
        case 0xA0:
            return new AndRegisterToA(RegisterName::B);
        case 0xA1:
            return new AndRegisterToA(RegisterName::C);
        case 0xA2:
            return new AndRegisterToA(RegisterName::D);
        case 0xA3:
            return new AndRegisterToA(RegisterName::E);
        case 0xA4:
            return new AndRegisterToA(RegisterName::H);
        case 0xA5:
            return new AndRegisterToA(RegisterName::L);
        case 0xA6:
            return new AndDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xE6:
            return new AndImmediateToA();
        case 0xB7:
            return new OrRegisterToA(RegisterName::A);
        case 0xB0:
            return new OrRegisterToA(RegisterName::B);
        case 0xB1:
            return new OrRegisterToA(RegisterName::C);
        case 0xB2:
            return new OrRegisterToA(RegisterName::D);
        case 0xB3:
            return new OrRegisterToA(RegisterName::E);
        case 0xB4:
            return new OrRegisterToA(RegisterName::H);
        case 0xB5:
            return new OrRegisterToA(RegisterName::L);
        case 0xB6:
            return new OrDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xF6:
            return new OrImmediateToA();
        case 0xAF:
            return new XorRegisterToA(RegisterName::A);
        case 0xA8:
            return new XorRegisterToA(RegisterName::B);
        case 0xA9:
            return new XorRegisterToA(RegisterName::C);
        case 0xAA:
            return new XorRegisterToA(RegisterName::D);
        case 0xAB:
            return new XorRegisterToA(RegisterName::E);
        case 0xAC:
            return new XorRegisterToA(RegisterName::H);
        case 0xAD:
            return new XorRegisterToA(RegisterName::L);
        case 0xAE:
            return new XorDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xEE:
            return new XorImmediateToA();
        case 0xBF:
            return new CpRegisterToA(RegisterName::A);
        case 0xB8:
            return new CpRegisterToA(RegisterName::B);
        case 0xB9:
            return new CpRegisterToA(RegisterName::C);
        case 0xBA:
            return new CpRegisterToA(RegisterName::D);
        case 0xBB:
            return new CpRegisterToA(RegisterName::E);
        case 0xBC:
            return new CpRegisterToA(RegisterName::H);
        case 0xBD:
            return new CpRegisterToA(RegisterName::L);
        case 0xBE:
            return new CpDoubleRegisterToA(DoubleRegisterName::HL);
        case 0xFE:
            return new CpImmediateToA();
        default:
            throw UnknownInstructionException(byteInstr);
    }
}
