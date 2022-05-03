#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "event/Event.h"

class Display{
private:

public:
    virtual void write(unsigned char color) = 0;
    virtual void HBlank() = 0;
    virtual void VBlank() = 0;
    virtual Event fetchEvent() = 0;
    virtual ~Display(){}
    virtual void update(unsigned int*) = 0;
};

#endif