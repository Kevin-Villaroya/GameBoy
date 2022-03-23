#ifndef __DISPLAY_H__
#define __DISPLAY_H__

class Display{
private:

public:
    virtual void write(unsigned char color) = 0;
    virtual void HBlank() = 0;
    virtual void VBlank() = 0;
    virtual ~Display(){}
};

#endif