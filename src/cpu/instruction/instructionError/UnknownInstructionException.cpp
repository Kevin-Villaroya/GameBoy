#include "UnknownInstructionException.h"

#include <sstream>

std::string UnknownInstructionException::createErrorMessage(unsigned char byteInstr, std::string message){
    std::stringstream ss;
    ss << "unknown instruction: " << unsigned(byteInstr) << " " << message;

    return ss.str();
}

UnknownInstructionException::UnknownInstructionException(unsigned char byteInstr, std::string message) : runtime_error(UnknownInstructionException::createErrorMessage(byteInstr, message)){   
}
