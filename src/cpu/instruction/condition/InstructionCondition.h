#ifndef __INSTRUCTION_CONDITION_H__
#define __INSTRUCTION_CONDITION_H__

class InstructionCondition {
	public:
		static bool NZ(const Memory& ram, const Registers& registers) {
			return !registers.isFlagZ();
		}
							   
	   static bool Z(const Memory& ram, const Registers& registers) {
			return registers.isFlagZ();
		}
							   
	   static bool NC(const Memory& ram, const Registers& registers) {
			return !registers.isFlagC();
		}
							   
	   static bool C(const Memory& ram, const Registers& registers) {
			return registers.isFlagC();
		}
};

#endif
