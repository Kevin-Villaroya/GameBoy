#ifndef __LOAD_REGISTER_TO_HL_H__
#define __LOAD_REGISTER_TO_HL_H__

#include "../../Instruction.h"

class LoadRegisterToHL : public Instruction
{
	private:
		RegisterName src;

	public:
		LoadRegisterToHL(RegisterName);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(const Memory&, unsigned short) override;

};

#endif
