#include "DecToHex.h"

std::string shortToHex(unsigned short value){
    char res[5];

	sprintf(res, "%04X", value);

    return res;
}

std::string charToHex(unsigned char value){
    char res[3];

	sprintf(res, "%02X", value);

    return res;
}