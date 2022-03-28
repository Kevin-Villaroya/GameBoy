#ifndef __LOAD_FROM_REGISTER_TO_ADDRESS_H__
#define __LOAD_FROM_REGISTER_TO_ADDRESS_H__

#include "../../Instruction.h"

class LoadFromRegisterToRelativeAddress : public Instruction
{
	private:
		RegisterName dest;
        RegisterName src;

	public:
		LoadFromRegisterToRelativeAddress(RegisterName dest, RegisterName src);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(const Memory&, unsigned short) override;
		std::string toString() override;

};

#endif
