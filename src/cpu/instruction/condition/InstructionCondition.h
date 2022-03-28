#ifndef __INSTRUCTION_CONDITION_H__
#define __INSTRUCTION_CONDITION_H__

#include <functional>

typedef std::function<bool(const Memory&, const Registers&)> Condition;

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

		static std::string getConditionName(Condition condition) {
			if(*condition.target<bool(*)(const Memory&, const Registers&)>() == InstructionCondition::NZ){
				return "NZ";
			}else if(*condition.target<bool(*)(const Memory&, const Registers&)>() == InstructionCondition::Z){
				return "Z";
			}else if(*condition.target<bool(*)(const Memory&, const Registers&)>() == InstructionCondition::NC){
				return "NC";
			}else if(*condition.target<bool(*)(const Memory&, const Registers&)>() == InstructionCondition::C){
				return "C";
			}else{
				return "";
			}
		}
};

#endif
