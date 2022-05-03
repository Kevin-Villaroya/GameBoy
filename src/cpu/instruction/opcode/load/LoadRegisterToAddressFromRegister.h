#ifndef __LOAD_REGISTER_TO_ADDRESS_FROM_REGISTER_H__
#define __LOAD_REGISTER_TO_ADDRESS_FROM_REGISTER_H__

#include "../../Instruction.h"

class LoadRegisterToAddressFromRegister : public Instruction
{
	private:
		DoubleRegisterName addr;
		RegisterName src;

	public:
		LoadRegisterToAddressFromRegister(DoubleRegisterName, RegisterName);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(Memory&, unsigned short) override;
		std::string toString() override;

};

#endif
