#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <string>
#include "Display.h"

class Terminal : public Display{
private:
    std::string palette[4];
public:
    Terminal();

    void write(unsigned char color);
    void HBlank();
    void VBlank();
};

#endif