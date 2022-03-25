#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <string>
#include "Display.h"

class Terminal : public Display{
private:
    std::string palette[4];
public:
    Terminal();

    void write(unsigned char color) override;
    void HBlank() override;
    void VBlank() override;
    Event fetchEvent() override;
};

#endif