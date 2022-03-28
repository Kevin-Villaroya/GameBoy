#include <iostream>
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
#include "opcode/add/AddHLToA.h"
#include "opcode/add/AddCarryRegisterToA.h"
#include "opcode/add/AddCarryHLToA.h"
#include "opcode/add/AddCarryImmediateToA.h"
#include "opcode/sub/SubRegisterToA.h"
#include "opcode/sub/SubHLToA.h"
#include "opcode/sub/SubImmediateToA.h"
#include "opcode/sub/SubCarryRegisterToA.h"
#include "opcode/sub/SubCarryHLToA.h"
#include "opcode/sub/SubCarryImmediateToA.h"
#include "opcode/and/AndRegisterToA.h"
#include "opcode/and/AndHLToA.h"
#include "opcode/and/AndImmediateToA.h"
#include "opcode/or/OrRegisterToA.h"
#include "opcode/or/OrHLToA.h"
#include "opcode/or/OrImmediateToA.h"
#include "opcode/xor/XorRegisterToA.h"
#include "opcode/xor/XorHLToA.h"
#include "opcode/xor/XorImmediateToA.h"
#include "opcode/cp/CpRegisterToA.h"
#include "opcode/cp/CpHLToA.h"
#include "opcode/cp/CpImmediateToA.h"
#include "opcode/add/AddDoubleRegisterToHL.h"
#include "opcode/add/AddImmediateToSP.h"
#include "opcode/swap/SwapRegister.h"
#include "opcode/swap/SwapHL.h"
#include "opcode/daa/DaaToA.h"
#include "opcode/cpl/CplToA.h"
#include "opcode/cpl/CplCarryFlag.h"
#include "opcode/set/SetCarryFlag.h"
#include "opcode/rl/RlCarryA.h"
#include "opcode/rl/RlA.h"
#include "opcode/rr/RrCarryA.h"
#include "opcode/rr/RrA.h"
#include "opcode/rl/RlCarryRegister.h"
#include "opcode/rl/RlCarryHL.h"
#include "opcode/rl/RlRegister.h"
#include "opcode/rl/RlHL.h"
#include "opcode/rr/RrCarryRegister.h"
#include "opcode/rr/RrCarryHL.h"
#include "opcode/rr/RrRegister.h"
#include "opcode/rr/RrHL.h"
#include "opcode/inc/IncrementHL.h"
#include "opcode/load/LoadFromAddressToRegister.h"
#include "opcode/load/LoadRegisterToAddressFromRegister.h"
#include "opcode/dec/DecrementRegister.h"
#include "opcode/dec/DecrementHL.h"
#include "opcode/load/LoadImmediateToRegister.h"
#include "opcode/jmp/JumpUnconditionalRelativeImmediate.h"
#include "opcode/inc/IncrementDoubleRegister.h"
#include "opcode/call/CallUnconditional.h"
#include "opcode/load/LoadAToImmediateAddress.h"
#include "opcode/ret/ReturnUnconditional.h"
#include "opcode/jmp/JumpConditionalImmediate.h"
#include "condition/InstructionCondition.h"
#include "opcode/call/CallConditional.h"
#include "opcode/load/LoadARegisterToHlIncrement.h"
#include "opcode/load/LoadARegisterToHlDecrement.h"
#include "opcode/bit/Bit.h"
#include "opcode/bit/BitHl.h"
#include "opcode/jmp/JumpConditionalRelativeImmediate.h"
#include "opcode/load/LoadFromRelativeAddressToRegister.h"
#include "opcode/load/LoadFromRegisterToRelativeAddress.h"
#include "opcode/di/DI.h"
#include "opcode/load/LoadRegisterToImmediateAddress.h"
#include "opcode/load/LoadFromImmediateRelativeAddressToRegister.h"

Instruction* InstructionFactory::forCode(const Memory& memory,unsigned short pc){
	unsigned char byteInstr = memory[pc];
    Instruction* instruction;

    switch(byteInstr){
        case 0xc3:
            instruction = new JumpUnconditionalImmediate();
             break;
        case 0x00:
            instruction = new Nop();
             break;
        case 0x2c:
            instruction =  new IncrementRegister(RegisterName::L);
             break;
        case 0x04:
            instruction =  new IncrementRegister(RegisterName::B);
             break;
        case 0x14:
            instruction =  new IncrementRegister(RegisterName::D);
             break;
        case 0x24:
            instruction =  new IncrementRegister(RegisterName::H);
             break;
        case 0x0c:
            instruction =  new IncrementRegister(RegisterName::C);
             break;
        case 0x1c:
            instruction =  new IncrementRegister(RegisterName::E);
             break;
        case 0x3c:
            instruction =  new IncrementRegister(RegisterName::A);
     	case 0x34:
            instruction =  new IncrementHL();
             break;
        case 0x40:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::B);
             break;
        case 0x50:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::B);
             break;
        case 0x60:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::B);
             break;
        case 0x41:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::C);
             break;
        case 0x51:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::C);
             break;
        case 0x61:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::C);
             break;
        case 0x42:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::D);
             break;
        case 0x52:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::D);
             break;
        case 0x62:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::D);
             break;
        case 0x43:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::E);
             break;
        case 0x53:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::E);
             break;
        case 0x63:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::E);
             break;
        case 0x44:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::H);
             break;
        case 0x54:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::H);
             break;
        case 0x64:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::H);
             break;
        case 0x45:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::L);
             break;
        case 0x55:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::L);
             break;
        case 0x65:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::L);
             break;
        case 0x47:
            instruction =  new LoadRegisterToRegister(RegisterName::B, RegisterName::A);
             break;
        case 0x57:
            instruction =  new LoadRegisterToRegister(RegisterName::D, RegisterName::A);
             break;
        case 0x67:
            instruction =  new LoadRegisterToRegister(RegisterName::H, RegisterName::A);
             break;
        case 0x48:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::B);
             break;
        case 0x58:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::B);
             break;
        case 0x68:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::B);
             break;
        case 0x78:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::B);
             break;
        case 0x49:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::C);
             break;
        case 0x59:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::C);
             break;
        case 0x69:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::C);
             break;
        case 0x79:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::C);
             break;
        case 0x4A:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::D);
             break;
        case 0x5A:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::D);
             break;
        case 0x6A:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::D);
             break;
        case 0x7A:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::D);
             break;
        case 0x4B:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::E);
             break;
        case 0x5B:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::E);
             break;
        case 0x6B:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::E);
             break;
        case 0x7B:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::E);
             break;
        case 0x4C:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::H);
             break;
        case 0x5C:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::H);
             break;
        case 0x6C:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::H);
             break;
        case 0x7C:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::H);
             break;
        case 0x4D:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::L);
             break;
        case 0x5D:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::L);
             break;
        case 0x6D:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::L);
             break;
        case 0x7D:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::L);
             break;
        case 0x4F:
            instruction =  new LoadRegisterToRegister(RegisterName::C, RegisterName::A);
             break;
        case 0x5F:
            instruction =  new LoadRegisterToRegister(RegisterName::E, RegisterName::A);
             break;
        case 0x6F:
            instruction =  new LoadRegisterToRegister(RegisterName::L, RegisterName::A);
             break;
        case 0x7F:
            instruction =  new LoadRegisterToRegister(RegisterName::A, RegisterName::A);
             break;
        case 0x01:
            instruction =  new LoadImmediateToDoubleRegister(DoubleRegisterName::BC);
             break;
        case 0x11:
            instruction =  new LoadImmediateToDoubleRegister(DoubleRegisterName::DE);
             break;
        case 0x21:
            instruction =  new LoadImmediateToDoubleRegister(DoubleRegisterName::HL);
             break;
        case 0x31:
            instruction =  new LoadImmediateToDoubleRegister(DoubleRegisterName::SP);
             break;
        case 0xF5:
            instruction =  new PushDoubleRegisterToStack(DoubleRegisterName::AF);
             break;
        case 0xC5:
            instruction =  new PushDoubleRegisterToStack(DoubleRegisterName::BC);
             break;
        case 0xD5:
            instruction =  new PushDoubleRegisterToStack(DoubleRegisterName::DE);
             break;
        case 0xE5:
            instruction =  new PushDoubleRegisterToStack(DoubleRegisterName::HL);
             break;
        case 0xF1:
            instruction =  new PopStackToDoubleRegister(DoubleRegisterName::AF);
             break;
        case 0xC1:
            instruction =  new PopStackToDoubleRegister(DoubleRegisterName::BC);
             break;
        case 0xD1:
            instruction =  new PopStackToDoubleRegister(DoubleRegisterName::DE);
             break;
        case 0xE1:
            instruction =  new PopStackToDoubleRegister(DoubleRegisterName::HL);
             break;
        case 0x87:
            instruction =  new AddRegisterToA(RegisterName::A);
             break;
        case 0x80:
            instruction =  new AddRegisterToA(RegisterName::B);
             break;
        case 0x81:
            instruction =  new AddRegisterToA(RegisterName::C);
             break;
        case 0x82:
            instruction =  new AddRegisterToA(RegisterName::D);
             break;
        case 0x83:
            instruction =  new AddRegisterToA(RegisterName::E);
             break;
        case 0x84:
            instruction =  new AddRegisterToA(RegisterName::H);
             break;
        case 0x85:
            instruction =  new AddRegisterToA(RegisterName::L);
             break;
        case 0x86:
            instruction =  new AddHLToA();
             break;
        case 0xC6:
            instruction =  new AddImmediateToA();
             break;
        case 0x8F:
            instruction =  new AddCarryRegisterToA(RegisterName::A);
             break;
        case 0x88:
            instruction =  new AddCarryRegisterToA(RegisterName::B);
             break;
        case 0x89:
            instruction =  new AddCarryRegisterToA(RegisterName::C);
             break;
        case 0x8A:
            instruction =  new AddCarryRegisterToA(RegisterName::D);
             break;
        case 0x8B:
            instruction =  new AddCarryRegisterToA(RegisterName::E);
             break;
        case 0x8C:
            instruction =  new AddCarryRegisterToA(RegisterName::H);
             break;
        case 0x8D:
            instruction =  new AddCarryRegisterToA(RegisterName::L);
             break;
        case 0x8E:
            instruction =  new AddCarryHLToA();
             break;
        case 0xCE:
            instruction =  new AddCarryImmediateToA();
             break;
        case 0x97:
            instruction =  new SubRegisterToA(RegisterName::A);
             break;
        case 0x90:
            instruction =  new SubRegisterToA(RegisterName::B);
             break;
        case 0x91:
            instruction =  new SubRegisterToA(RegisterName::C);
             break;
        case 0x92:
            instruction =  new SubRegisterToA(RegisterName::D);
             break;
        case 0x93:
            instruction =  new SubRegisterToA(RegisterName::E);
             break;
        case 0x94:
            instruction =  new SubRegisterToA(RegisterName::H);
             break;
        case 0x95:
            instruction =  new SubRegisterToA(RegisterName::L);
             break;
        case 0x96:
            instruction =  new SubHLToA();
             break;
        case 0xD6:
            instruction =  new SubImmediateToA();
             break;
        case 0x9F:
            instruction =  new SubCarryRegisterToA(RegisterName::A);
             break;
        case 0x98:
            instruction =  new SubCarryRegisterToA(RegisterName::B);
             break;
        case 0x99:
            instruction =  new SubCarryRegisterToA(RegisterName::C);
             break;
        case 0x9A:
            instruction =  new SubCarryRegisterToA(RegisterName::D);
             break;
        case 0x9B:
            instruction =  new SubCarryRegisterToA(RegisterName::E);
             break;
        case 0x9C:
            instruction =  new SubCarryRegisterToA(RegisterName::H);
             break;
        case 0x9D:
            instruction =  new SubCarryRegisterToA(RegisterName::L);    
        case 0x9E:
            instruction =  new SubCarryHLToA();
             break;
        case 0xDE:
            instruction =  new SubCarryImmediateToA();
             break;
        case 0xA7:
            instruction =  new AndRegisterToA(RegisterName::A);
             break;
        case 0xA0:
            instruction =  new AndRegisterToA(RegisterName::B);
             break;
        case 0xA1:
            instruction =  new AndRegisterToA(RegisterName::C);
             break;
        case 0xA2:
            instruction =  new AndRegisterToA(RegisterName::D);
             break;
        case 0xA3:
            instruction =  new AndRegisterToA(RegisterName::E);
             break;
        case 0xA4:
            instruction =  new AndRegisterToA(RegisterName::H);
             break;
        case 0xA5:
            instruction =  new AndRegisterToA(RegisterName::L);
             break;
        case 0xA6:
            instruction =  new AndHLToA();
             break;
        case 0xE6:
            instruction =  new AndImmediateToA();
             break;
        case 0xB7:
            instruction =  new OrRegisterToA(RegisterName::A);
             break;
        case 0xB0:
            instruction =  new OrRegisterToA(RegisterName::B);
             break;
        case 0xB1:
            instruction =  new OrRegisterToA(RegisterName::C);
             break;
        case 0xB2:
            instruction =  new OrRegisterToA(RegisterName::D);
             break;
        case 0xB3:
            instruction =  new OrRegisterToA(RegisterName::E);
             break;
        case 0xB4:
            instruction =  new OrRegisterToA(RegisterName::H);
             break;
        case 0xB5:
            instruction =  new OrRegisterToA(RegisterName::L);
             break;
        case 0xB6:
            instruction =  new OrHLToA();
             break;
        case 0xF6:
            instruction =  new OrImmediateToA();
             break;
        case 0xAF:
            instruction =  new XorRegisterToA(RegisterName::A);
             break;
        case 0xA8:
            instruction =  new XorRegisterToA(RegisterName::B);
             break;
        case 0xA9:
            instruction =  new XorRegisterToA(RegisterName::C);
             break;
        case 0xAA:
            instruction =  new XorRegisterToA(RegisterName::D);
             break;
        case 0xAB:
            instruction =  new XorRegisterToA(RegisterName::E);
             break;
        case 0xAC:
            instruction =  new XorRegisterToA(RegisterName::H);
             break;
        case 0xAD:
            instruction =  new XorRegisterToA(RegisterName::L);
             break;
        case 0xAE:
            instruction =  new XorHLToA();
             break;
        case 0xEE:
            instruction =  new XorImmediateToA();
             break;
        case 0xBF:
            instruction =  new CpRegisterToA(RegisterName::A);
             break;
        case 0xB8:
            instruction =  new CpRegisterToA(RegisterName::B);
             break;
        case 0xB9:
            instruction =  new CpRegisterToA(RegisterName::C);
             break;
        case 0xBA:
            instruction =  new CpRegisterToA(RegisterName::D);
             break;
        case 0xBB:
            instruction =  new CpRegisterToA(RegisterName::E);
             break;
        case 0xBC:
            instruction =  new CpRegisterToA(RegisterName::H);
             break;
        case 0xBD:
            instruction =  new CpRegisterToA(RegisterName::L);
             break;
        case 0xBE:
            instruction =  new CpHLToA();
             break;
        case 0xFE:
            instruction =  new CpImmediateToA();
             break;
        case 0x09:
            instruction =  new AddDoubleRegisterToHL(DoubleRegisterName::BC);
             break;
        case 0x19:
            instruction =  new AddDoubleRegisterToHL(DoubleRegisterName::DE);
             break;
        case 0x29:
            instruction =  new AddDoubleRegisterToHL(DoubleRegisterName::HL);
             break;
        case 0x39:
            instruction =  new AddDoubleRegisterToHL(DoubleRegisterName::SP);
             break;
        case 0xE8:
            instruction =  new AddImmediateToSP();
             break;
        case 0x27:
            instruction =  new DaaToA();
             break;
        case 0x2F:
            instruction =  new CplToA();
             break;
        case 0x3F:
            instruction =  new CplCarryFlag();
             break;
        case 0x37:
            instruction =  new SetCarryFlag();
             break;
        case 0x07:
            instruction =  new RlCarryA();
             break;
        case 0x17:
            instruction =  new RlA();
             break;
        case 0x0F:
            instruction =  new RrCarryA();
             break;
        case 0x1F:
            instruction =  new RrA();            
        case 0x7E:
        	instruction =  new LoadFromAddressToRegister(RegisterName::A, DoubleRegisterName::HL);
             break;
        case 0x46:
        	instruction =  new LoadFromAddressToRegister(RegisterName::B, DoubleRegisterName::HL);
             break;
        case 0x4E:
        	instruction =  new LoadFromAddressToRegister(RegisterName::C, DoubleRegisterName::HL);
             break;
        case 0x56:
        	instruction =  new LoadFromAddressToRegister(RegisterName::D, DoubleRegisterName::HL);
             break;
        case 0x5E:
        	instruction =  new LoadFromAddressToRegister(RegisterName::E, DoubleRegisterName::HL);
             break;
        case 0x66:
        	instruction =  new LoadFromAddressToRegister(RegisterName::H, DoubleRegisterName::HL);
             break;
        case 0x6E:
        	instruction =  new LoadFromAddressToRegister(RegisterName::L, DoubleRegisterName::HL);
             break;
        case 0x70:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::B);
             break;
        case 0x71:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::C);
             break;
        case 0x72:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::D);
             break;
        case 0x73:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::E);
             break;
        case 0x74:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::H);
        	
		case 0x75:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::L);
             break;
        case 0x3D:
        	instruction =  new DecrementRegister(RegisterName::A);
             break;
        case 0x05:
        	instruction =  new DecrementRegister(RegisterName::B);
             break;
        case 0x0D:
        	instruction =  new DecrementRegister(RegisterName::C);
             break;
        case 0x15:
        	instruction =  new DecrementRegister(RegisterName::D);
             break;
        case 0x1D:
        	instruction =  new DecrementRegister(RegisterName::E);
             break;
        case 0x25:
        	instruction =  new DecrementRegister(RegisterName::H);
             break;
        case 0x2D:
        	instruction =  new DecrementRegister(RegisterName::H);
             break;
        case 0x35:
        	instruction =  new DecrementHL();
             break;
        case 0x06:
        	instruction =  new LoadImmediateToRegister(RegisterName::B);
             break;
        case 0x0E:
        	instruction =  new LoadImmediateToRegister(RegisterName::C);
             break;
        case 0x16:
        	instruction =  new LoadImmediateToRegister(RegisterName::D);
             break;
        case 0x1E:
        	instruction =  new LoadImmediateToRegister(RegisterName::E);
             break;
        case 0x26:
        	instruction =  new LoadImmediateToRegister(RegisterName::H);
             break;
        case 0x2E:
        	instruction =  new LoadImmediateToRegister(RegisterName::L);
             break;
        case 0x3E:
        	instruction =  new LoadImmediateToRegister(RegisterName::A);
             break;
        case 0x18:
        	instruction =  new JumpUnconditionalRelativeImmediate();
             break;
        case 0x02:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::BC, RegisterName::A);
        	
    	case 0x12:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::DE, RegisterName::A);
             break;
        case 0x77:
        	instruction =  new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::A);
             break;
        case 0x03:
        	instruction =  new IncrementDoubleRegister(DoubleRegisterName::BC);
             break;
        case 0x13:
        	instruction =  new IncrementDoubleRegister(DoubleRegisterName::DE);
             break;
        case 0x23:
        	instruction =  new IncrementDoubleRegister(DoubleRegisterName::HL);
             break;
        case 0x33:
        	instruction =  new IncrementDoubleRegister(DoubleRegisterName::SP);
             break;
        case 0xCD:
        	instruction =  new CallUnconditional();
             break;
        case 0xE0:
        	instruction =  new LoadAToImmediateAddress();
             break;
        case 0xC9:
        	instruction =  new ReturnUnconditional();
             break;
        case 0xC2:
        	instruction =  new JumpConditionalImmediate(InstructionCondition::NZ);
             break;
        case 0xCA:
        	instruction =  new JumpConditionalImmediate(InstructionCondition::Z);
             break;
        case 0xD2:
        	instruction =  new JumpConditionalImmediate(InstructionCondition::NC);
             break;
        case 0xDA:
        	instruction =  new JumpConditionalImmediate(InstructionCondition::C);
             break;
        case 0xCC:
            instruction =  new CallConditional(InstructionCondition::Z);
             break;
        case 0xDC:
            instruction =  new CallConditional(InstructionCondition::C);
             break;
        case 0xC4:
            instruction =  new CallConditional(InstructionCondition::NZ);
             break;
        case 0xD4:
            instruction =  new CallConditional(InstructionCondition::NC);
             break;
        case 0x22:
            instruction =  new LoadARegisterToHlIncrement();
             break;
        case 0x32:
            instruction =  new LoadARegisterToHlDecrement();
             break;
        case 0x20:
            instruction =  new JumpConditionalRelativeImmediate(InstructionCondition::NZ);
             break;
        case 0x30:
            instruction =  new JumpConditionalRelativeImmediate(InstructionCondition::NC);
             break;
        case 0x28:
            instruction =  new JumpConditionalRelativeImmediate(InstructionCondition::Z);
             break;
        case 0x38:
            instruction =  new JumpConditionalRelativeImmediate(InstructionCondition::C);
             break;
        case 0xF2:
            instruction =  new LoadFromRelativeAddressToRegister(RegisterName::A, RegisterName::C);
             break;
        case 0xE2:
            instruction =  new LoadFromRegisterToRelativeAddress(RegisterName::C, RegisterName::A);  
            break;
        case 0x0A:
            instruction =  new LoadFromAddressToRegister(RegisterName::A, DoubleRegisterName::BC);
             break;
        case 0x1A:
            instruction =  new LoadFromAddressToRegister(RegisterName::A, DoubleRegisterName::DE);
             break;
        case 0xF3:
            instruction =  new DI();
             break;
        case 0xEA:
            instruction =  new LoadRegisterToImmediateAddress(RegisterName::A);
             break;
        case 0xF0:
            instruction =  new LoadFromImmediateRelativeAddressToRegister(RegisterName::A);
             break;
        case 0xCB:
        	instruction =  InstructionFactory::forCodeCb(memory[pc + 1]);
            break;
        default:
            throw UnknownInstructionException(0x00 + byteInstr, "8 bit opcode");
	}

    instruction->opCode = byteInstr;

    return instruction;
}
    
Instruction* InstructionFactory::forCodeCb(unsigned char byteInstr){
    Instruction* instruction;

	switch(byteInstr){
		case 0x07:
	        instruction =  new RlCarryRegister(RegisterName::A);
	        break;
	    case 0x00:
	        instruction =  new RlCarryRegister(RegisterName::B);
	        break;
	    case 0x01:
	        instruction =  new RlCarryRegister(RegisterName::C);
	        break;
	    case 0x02:
	        instruction =  new RlCarryRegister(RegisterName::D);
	        break;
	    case 0x03:
	        instruction =  new RlCarryRegister(RegisterName::E);
	        break;
	    case 0x04:
	        instruction =  new RlCarryRegister(RegisterName::H);
	        break;
	    case 0x05:
	        instruction =  new RlCarryRegister(RegisterName::L);
	        break;
	    case 0x06:
	        instruction =  new RlCarryHL();
	        break;
	    case 0x17:
	        instruction =  new RlRegister(RegisterName::A);
	        break;
	    case 0x10:
	        instruction =  new RlRegister(RegisterName::B);
	        break;
	    case 0x11:
	        instruction =  new RlRegister(RegisterName::C);
	        break;
	    case 0x12:
	        instruction =  new RlRegister(RegisterName::D);
	        break;
	    case 0x13:
	        instruction =  new RlRegister(RegisterName::E);
	        break;
	    case 0x14:
	        instruction =  new RlRegister(RegisterName::H);
	        break;
	    case 0x15:
	        instruction =  new RlRegister(RegisterName::L);
	        break;
	    case 0x16:
	        instruction =  new RlHL();
	        break;
	    case 0x0F:
	        instruction =  new RrCarryRegister(RegisterName::A);
	        break;
	    case 0x08:
	        instruction =  new RrCarryRegister(RegisterName::B);
	        break;
	    case 0x09:
	        instruction =  new RrCarryRegister(RegisterName::C);
	        break;
	    case 0x0A:
	        instruction =  new RrCarryRegister(RegisterName::D);
	        break;
	    case 0x0B:
	        instruction =  new RrCarryRegister(RegisterName::E);
	        break;
	    case 0x0C:
	        instruction =  new RrCarryRegister(RegisterName::H);
	        break;
	    case 0x0D:
	        instruction =  new RrCarryRegister(RegisterName::L);
	        break;
	    case 0x0E:
	        instruction =  new RrCarryHL();
	        break;
	    case 0x1F:
	        instruction =  new RrRegister(RegisterName::A);
	        break;
	    case 0x18:
	        instruction =  new RrRegister(RegisterName::B);
	        break;
	    case 0x19:
	        instruction =  new RrRegister(RegisterName::C);
	        break;
	    case 0x1A:
	        instruction =  new RrRegister(RegisterName::D);
	        break;
	    case 0x1B:
	        instruction =  new RrRegister(RegisterName::E);
	        break;
	    case 0x1C:
	        instruction =  new RrRegister(RegisterName::H);
	        break;
	    case 0x1D:
	        instruction =  new RrRegister(RegisterName::L);
	        break;
	    case 0x1E:
	        instruction =  new RrHL();
	        break;
	    case 0x37:
	        instruction =  new SwapRegister(RegisterName::A);
	        break;
	    case 0x30:
	        instruction =  new SwapRegister(RegisterName::B);
	        break;
	    case 0x31:
	        instruction =  new SwapRegister(RegisterName::C);
	        break;
	    case 0x32:
	        instruction =  new SwapRegister(RegisterName::D);
	        break;
	    case 0x33:
	        instruction =  new SwapRegister(RegisterName::E);
	        break;
	    case 0x34:
	        instruction =  new SwapRegister(RegisterName::H);
	        break;
	    case 0x35:
	        instruction =  new SwapRegister(RegisterName::L);
	        break;
	    case 0x36:
	     	instruction =  new SwapHL();
             break;
        case 0x40:
            instruction =  new Bit(0, RegisterName::B);
             break;
        case 0x41:
            instruction =  new Bit(0, RegisterName::C);
             break;
        case 0x42:
            instruction =  new Bit(0, RegisterName::D);
             break;
        case 0x43:
            instruction =  new Bit(0, RegisterName::E);
             break;
        case 0x44:
            instruction =  new Bit(0, RegisterName::H);
             break;
        case 0x45:
            instruction =  new Bit(0, RegisterName::L);
             break;
        case 0x46:
            instruction =  new BitHl(0);
             break;
        case 0x47:
            instruction =  new Bit(0, RegisterName::A);
             break;
        case 0x48:
            instruction =  new Bit(1, RegisterName::B);
             break;
        case 0x49:
            instruction =  new Bit(1, RegisterName::C);
             break;
        case 0x4A:
            instruction =  new Bit(1, RegisterName::D);
             break;
        case 0x4B:
            instruction =  new Bit(1, RegisterName::E);
             break;
        case 0x4C:
            instruction =  new Bit(1, RegisterName::H);
             break;
        case 0x4D:
            instruction =  new Bit(1, RegisterName::L);
             break;
        case 0x4E:
            instruction =  new BitHl(1);
             break;
        case 0x4F:
            instruction =  new Bit(1, RegisterName::A);
             break;
        case 0x50:
            instruction =  new Bit(2, RegisterName::B);
             break;
        case 0x51:
            instruction =  new Bit(2, RegisterName::C);
             break;
        case 0x52:
            instruction =  new Bit(2, RegisterName::D);
             break;
        case 0x53:
            instruction =  new Bit(2, RegisterName::E);
             break;
        case 0x54:
            instruction =  new Bit(2, RegisterName::H);
             break;
        case 0x55:
            instruction =  new Bit(2, RegisterName::L);
             break;
        case 0x56:
            instruction =  new BitHl(2);
             break;
        case 0x57:
            instruction =  new Bit(2, RegisterName::A);
             break;
        case 0x58:
            instruction =  new Bit(3, RegisterName::B);
             break;
        case 0x59:
            instruction =  new Bit(3, RegisterName::C);
             break;
        case 0x5A:
            instruction =  new Bit(3, RegisterName::D);
             break;
        case 0x5B:
            instruction =  new Bit(3, RegisterName::E);
             break;
        case 0x5C:
            instruction =  new Bit(3, RegisterName::H);
             break;
        case 0x5D:
            instruction =  new Bit(3, RegisterName::L);
             break;
        case 0x5E:
            instruction =  new BitHl(3);
             break;
        case 0x5F:
            instruction =  new Bit(3, RegisterName::A);
             break;
        case 0x60:
            instruction =  new Bit(4, RegisterName::B);
             break;
        case 0x61:
            instruction =  new Bit(4, RegisterName::C);
             break;
        case 0x62:
            instruction =  new Bit(4, RegisterName::D);
             break;
        case 0x63:
            instruction =  new Bit(4, RegisterName::E);
             break;
        case 0x64:
            instruction =  new Bit(4, RegisterName::H);
             break;
        case 0x65:
            instruction =  new Bit(4, RegisterName::L);
             break;
        case 0x66:
            instruction =  new BitHl(4);
             break;
        case 0x67:
            instruction =  new Bit(4, RegisterName::A);
             break;
        case 0x68:
            instruction =  new Bit(5, RegisterName::B);
             break;
        case 0x69:
            instruction =  new Bit(5, RegisterName::C);
             break;
        case 0x6A:
            instruction =  new Bit(5, RegisterName::D);
             break;
        case 0x6B:
            instruction =  new Bit(5, RegisterName::E);
             break;
        case 0x6C:
            instruction =  new Bit(5, RegisterName::H);
             break;
        case 0x6D:
            instruction =  new Bit(5, RegisterName::L);
             break;
        case 0x6E:
            instruction =  new BitHl(5);
             break;
        case 0x6F:
            instruction =  new Bit(5, RegisterName::A);
             break;
        case 0x70:
            instruction =  new Bit(6, RegisterName::B);
             break;
        case 0x71:
            instruction =  new Bit(6, RegisterName::C);
             break;
        case 0x72:
            instruction =  new Bit(6, RegisterName::D);
             break;
        case 0x73:
            instruction =  new Bit(6, RegisterName::E);
             break;
        case 0x74:
            instruction =  new Bit(6, RegisterName::H);
             break;
        case 0x75:
            instruction =  new Bit(6, RegisterName::L);
             break;
        case 0x76:
            instruction =  new BitHl(6);
             break;
        case 0x77:
            instruction =  new Bit(6, RegisterName::A);
             break;
        case 0x78:
            instruction =  new Bit(7, RegisterName::B);
             break;
        case 0x79:
            instruction =  new Bit(7, RegisterName::C);
             break;
        case 0x7A:
            instruction =  new Bit(7, RegisterName::D);
             break;
        case 0x7B:
            instruction =  new Bit(7, RegisterName::E);
             break;
        case 0x7C:
            instruction =  new Bit(7, RegisterName::H);
             break;
        case 0x7D:
            instruction =  new Bit(7, RegisterName::L);
             break;
        case 0x7E:
            instruction =  new BitHl(7);
             break;
        case 0x7F:
            instruction =  new Bit(7, RegisterName::A);
            break;
	    default:
        	throw UnknownInstructionException(0xCB00 + byteInstr, "16 bit opcode");       
    }
    instruction->opCode = 0xCB00 + byteInstr;

    return instruction;
}
