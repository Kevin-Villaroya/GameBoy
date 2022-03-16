#ifndef __LOAD_HL_TO_REGISTER_H__
#define __LOAD_HL_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadHLToRegister : public Instruction
{
	private:
		RegisterName dest;

	public:
		LoadHLToRegister(RegisterName);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(const Memory&, unsigned short) override;

};

#endif
