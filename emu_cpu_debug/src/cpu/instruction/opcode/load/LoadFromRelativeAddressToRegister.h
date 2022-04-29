#ifndef __LOAD_FROM_ADDRESS_TO_REGISTER_H__
#define __LOAD_FROM_ADDRESS_TO_REGISTER_H__

#include "../../Instruction.h"

class LoadFromRelativeAddressToRegister : public Instruction
{
	private:
		RegisterName dest;
        RegisterName addressRegister;

	public:
		LoadFromRelativeAddressToRegister(RegisterName, RegisterName);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(const Memory&, unsigned short) override;
		std::string toString() override;

};

#endif
