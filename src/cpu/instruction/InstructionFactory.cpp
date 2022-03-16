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
#include "opcode/load/LoadHLToRegister.h"
#include "opcode/load/LoadRegisterToAddressFromRegister.h"
#include "opcode/dec/DecrementRegister.h"
#include "opcode/dec/DecrementHL.h"
#include "opcode/load/LoadImmediateToRegister.h"
#include "opcode/jmp/JumpUnconditionalRelativeImmediate.h"
#include "opcode/inc/IncrementDoubleRegister.h"
#include "opcode/call/CallUnconditional.h"
#include "opcode/load/LoadAToImmediateAddress.h"
#include "opcode/ret/ReturnUnconditional.h"

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
     	case 0x34:
            return new IncrementHL();
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
            return new AddHLToA();
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
            return new AddCarryHLToA();
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
            return new SubHLToA();
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
            return new SubCarryHLToA();
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
            return new AndHLToA();
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
            return new OrHLToA();
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
            return new XorHLToA();
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
            return new CpHLToA();
        case 0xFE:
            return new CpImmediateToA();
        case 0x09:
            return new AddDoubleRegisterToHL(DoubleRegisterName::BC);
        case 0x19:
            return new AddDoubleRegisterToHL(DoubleRegisterName::DE);
        case 0x29:
            return new AddDoubleRegisterToHL(DoubleRegisterName::HL);
        case 0x39:
            return new AddDoubleRegisterToHL(DoubleRegisterName::SP);
        case 0xE8:
            return new AddImmediateToSP();
        /*case 0xCB37:
            return new SwapRegister(RegisterName::A);
        case 0xCB30:
            return new SwapRegister(RegisterName::B);
        case 0xCB31:
            return new SwapRegister(RegisterName::C);
        case 0xCB32:
            return new SwapRegister(RegisterName::D);
        case 0xCB33:
            return new SwapRegister(RegisterName::E);
        case 0xCB34:
            return new SwapRegister(RegisterName::H);
        case 0xCB35:
            return new SwapRegister(RegisterName::L);
        case 0xCB36:
            return new SwapHL();*/
        case 0x27:
            return new DaaToA();
        case 0x2F:
            return new CplToA();
        case 0x3F:
            return new CplCarryFlag();
        case 0x37:
            return new SetCarryFlag();
        case 0x07:
            return new RlCarryA();
        case 0x17:
            return new RlA();
        case 0x0F:
            return new RrCarryA();
        case 0x1F:
            return new RrA();
        /*case 0xCB07:
            return new RlCarryRegister(RegisterName::A);
        case 0xCB00:
            return new RlCarryRegister(RegisterName::B);
        case 0xCB01:
            return new RlCarryRegister(RegisterName::C);
        case 0xCB02:
            return new RlCarryRegister(RegisterName::D);
        case 0xCB03:
            return new RlCarryRegister(RegisterName::E);
        case 0xCB04:
            return new RlCarryRegister(RegisterName::H);
        case 0xCB05:
            return new RlCarryRegister(RegisterName::L);
        case 0xCB06:
            return new RlCarryHL();
        case 0xCB17:
            return new RlRegister(RegisterName::A);
        case 0xCB10:
            return new RlRegister(RegisterName::B);
        case 0xCB11:
            return new RlRegister(RegisterName::C);
        case 0xCB12:
            return new RlRegister(RegisterName::D);
        case 0xCB13:
            return new RlRegister(RegisterName::E);
        case 0xCB14:
            return new RlRegister(RegisterName::H);
        case 0xCB15:
            return new RlRegister(RegisterName::L);
        case 0xCB16:
            return new RlHL();
        case 0xCB0F:
            return new RrCarryRegister(RegisterName::A);
        case 0xCB08:
            return new RrCarryRegister(RegisterName::B);
        case 0xCB09:
            return new RrCarryRegister(RegisterName::C);
        case 0xCB0A:
            return new RrCarryRegister(RegisterName::D);
        case 0xCB0B:
            return new RrCarryRegister(RegisterName::E);
        case 0xCB0C:
            return new RrCarryRegister(RegisterName::H);
        case 0xCB0D:
            return new RrCarryRegister(RegisterName::L);
        case 0xCB0E:
            return new RrCarryHL();
        case 0xCB1F:
            return new RrRegister(RegisterName::A);
        case 0xCB18:
            return new RrRegister(RegisterName::B);
        case 0xCB19:
            return new RrRegister(RegisterName::C);
        case 0xCB1A:
            return new RrRegister(RegisterName::D);
        case 0xCB1B:
            return new RrRegister(RegisterName::E);
        case 0xCB1C:
            return new RrRegister(RegisterName::H);
        case 0xCB1D:
            return new RrRegister(RegisterName::L);
        case 0xCB1E:
            return new RrHL();*/
            
        case 0x7E:
        	return new LoadHLToRegister(RegisterName::A);
        	
        case 0x46:
        	return new LoadHLToRegister(RegisterName::B);
        	
        case 0x4E:
        	return new LoadHLToRegister(RegisterName::C);
        	
        case 0x56:
        	return new LoadHLToRegister(RegisterName::D);
        	
        case 0x5E:
        	return new LoadHLToRegister(RegisterName::E);
        	
        case 0x66:
        	return new LoadHLToRegister(RegisterName::H);
        	
        case 0x6E:
        	return new LoadHLToRegister(RegisterName::L);
        	
        case 0x70:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::B);
        	
        case 0x71:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::C);
        	
        case 0x72:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::D);
        	
        case 0x73:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::E);
        	
        case 0x74:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::H);
        	
		case 0x75:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::L);
        	
        case 0x3D:
        	return new DecrementRegister(RegisterName::A);
        	
        case 0x05:
        	return new DecrementRegister(RegisterName::B);
        	
        case 0x0D:
        	return new DecrementRegister(RegisterName::C);
        	
        case 0x15:
        	return new DecrementRegister(RegisterName::D);
        	
        case 0x1D:
        	return new DecrementRegister(RegisterName::E);
        	
        case 0x25:
        	return new DecrementRegister(RegisterName::H);
        	
        case 0x2D:
        	return new DecrementRegister(RegisterName::H);
        	
        case 0x35:
        	return new DecrementHL();
        	
        case 0x06:
        	return new LoadImmediateToRegister(RegisterName::B);
        	
        case 0x0E:
        	return new LoadImmediateToRegister(RegisterName::C);
        	
        case 0x16:
        	return new LoadImmediateToRegister(RegisterName::D);
        	
        case 0x1E:
        	return new LoadImmediateToRegister(RegisterName::E);
        	
        case 0x26:
        	return new LoadImmediateToRegister(RegisterName::H);
        	
        case 0x2E:
        	return new LoadImmediateToRegister(RegisterName::L);
        	
        case 0x18:
        	return new JumpUnconditionalRelativeImmediate();
        	
        case 0x02:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::BC, RegisterName::A);
        	
    	case 0x12:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::DE, RegisterName::A);
        	
        case 0x77:
        	return new LoadRegisterToAddressFromRegister(DoubleRegisterName::HL, RegisterName::A);
        	
        case 0x03:
        	return new IncrementDoubleRegister(DoubleRegisterName::BC);
        	
        case 0x13:
        	return new IncrementDoubleRegister(DoubleRegisterName::DE);
        	
        case 0x23:
        	return new IncrementDoubleRegister(DoubleRegisterName::HL);
        	
        case 0x33:
        	return new IncrementDoubleRegister(DoubleRegisterName::SP);
        	
        case 0xCD:
        	return new CallUnconditional();
        	
        case 0xE0:
        	return new LoadAToImmediateAddress();
        
        case 0xC9:
        	return new ReturnUnconditional();
        	
        default:
            throw UnknownInstructionException(byteInstr);
    }
}
