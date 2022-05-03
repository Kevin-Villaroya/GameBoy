#ifndef __LOAD_HL_TO_REGISTER_H__
#define __LOAD_HL_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadFromAddressToRegister : public Instruction
{
	private:
		RegisterName dest;
		DoubleRegisterName src;

	public:
		LoadFromAddressToRegister(RegisterName dest, DoubleRegisterName src);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(Memory&, unsigned short) override;
		std::string toString() override;

};

#endif
