#ifndef __LOAD_REGISTER_TO_ADDRESS_FROM_IMMEDIATE_H__
#define __LOAD_REGISTER_TO_ADDRESS_FROM_IMMEDIATE_H__

#include "../../Instruction.h"

class LoadRegisterToAddressFromImmediate : public Instruction
{
	private:
		DoubleRegisterName addr;
		unsigned char parameter;

	public:
		LoadRegisterToAddressFromImmediate(DoubleRegisterName);

		void execute(Memory& ram, Registers& registers) override;
		unsigned int getSize() override;
		unsigned int getTiming() override;
		void setParameters(const Memory&, unsigned short) override;
		std::string toString() override;

};

#endif
