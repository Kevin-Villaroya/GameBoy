#include "UnknownInstructionException.h"

#include <sstream>

std::string UnknownInstructionException::createErrorMessage(unsigned char byteInstr){
    std::stringstream ss;
    ss << "unknown instruction: " << unsigned(byteInstr);

    return ss.str();
}

UnknownInstructionException::UnknownInstructionException(unsigned char byteInstr) : runtime_error(UnknownInstructionException::createErrorMessage(byteInstr)){   
}
