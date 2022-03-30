#include "UnknownInstructionException.h"
#include "../../../util/DecToHex.h"

#include <sstream>

std::string UnknownInstructionException::createErrorMessage(unsigned short byteInstr, std::string message){
    std::stringstream ss;
    ss << "unknown instruction: " << shortToHex(byteInstr) << " " << message;

    return ss.str();
}

UnknownInstructionException::UnknownInstructionException(unsigned short byteInstr, std::string message) : runtime_error(UnknownInstructionException::createErrorMessage(byteInstr, message)){   
}
