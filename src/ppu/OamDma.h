#ifndef __OAM_DMA_H__
#define __OAM_DMA_H__
#define DMA_REGISTER 0xFF46

class OamDma{
    private:
        const int offSet = 0xFE00;
        bool active;
        unsigned char bytePtr;
        unsigned char delay;

    public:
        void dmaTick(void*);
        void dmaStart();
        bool isActive();

};

#endif