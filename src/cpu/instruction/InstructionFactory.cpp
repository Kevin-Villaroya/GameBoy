#include "InstructionFactory.h"
#include "instructionError/UnknownInstructionException.h"

#include "opcode/jmp/JumpUnconditionalImmediate.h"
#include "opcode/nop/Nop.h"
#include "opcode/inc/IncrementRegister.h"
#include "opcode/load/LoadRegisterToRegister.h"
#include "opcode/load/LoadImmediateToDoubleRegister.h"
#include "opcode/push/PushDoubleRegisterToStack.h"
#include "opcode/pop/PopStackToDoubleRegister.h"

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
        default:
            throw UnknownInstructionException(byteInstr);
    }
}
