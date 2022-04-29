#ifndef __UNKNOWN_INSTRUCTION_H__
#define __UNKNOWN_INSTRUCTION_H__

#include <stdexcept>
#include <string>

class UnknownInstructionException : public std::runtime_error{
    private:

        static std::string createErrorMessage(unsigned short byteInstr, std::string message);
    public:
        UnknownInstructionException(unsigned short byteInstr, std::string message);
};

#endif