#include "InstructionFactory.h"
#include "instructionError/UnknownInstructionException.h"

Instruction* InstructionFactory::forCode(unsigned char byteInstr){
    switch(byteInstr){
        default:
            throw UnknownInstructionException(byteInstr);
    }
}