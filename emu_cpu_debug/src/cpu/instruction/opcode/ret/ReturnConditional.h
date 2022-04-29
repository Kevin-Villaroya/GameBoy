#ifndef __RETURN_CONDITIONAL_H__
#define __RETURN_CONDITIONAL_H__

#include "../../Instruction.h"
#include "../../condition/InstructionCondition.h"

class ReturnConditional : public Instruction{
	private:
		Condition condition;
    int timing;
    public:
    	ReturnConditional(Condition condition);

      void execute(Memory&, Registers&) override;
      unsigned int getSize() override;
      unsigned int getTiming() override;
      void setParameters(const Memory&, unsigned short) override;
      std::string toString() override;
};
#endif
