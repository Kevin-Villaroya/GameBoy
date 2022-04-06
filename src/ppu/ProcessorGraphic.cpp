#include "ProcessorGraphic.h"
#include "../util/BitMath.h"
#include <iostream>

ProcessorGraphic::ProcessorGraphic(Display* screen, Memory* ram) : screen(screen), ram(ram){
    this->x = 0;
    this->ticks = 0;
    this->currentState = ProcessorGraphicState::OAMSearch;
    this->hasToRenderTiles = false;
    this->hasToRenderSprites = false;
}

void ProcessorGraphic::tick(){
    this->setLCDStatus();

    this->ticks++;

    switch (this->currentState){
        case ProcessorGraphicState::OAMSearch:
            this->oamSearch();
            break;

        case ProcessorGraphicState::PixelTransfer:
            this->pixelTransfer();
            break;

        case ProcessorGraphicState::HBlank:
            this->hBlank();
            break;

        case ProcessorGraphicState::VBlank:
            this->vBlank();
            break;

        default:
            break;
    }
}

void ProcessorGraphic::oamSearch(){
    if(this->ticks == 40){
        this->hasToRenderTiles = testBit(this->ram->get(Memory::LCDC), 0);
        this->hasToRenderSprites = testBit(this->ram->get(Memory::LCDC), 1);

        this->x = 0;

        this->fetcher.start(this->ram);
        this->currentState = ProcessorGraphicState::PixelTransfer;
    }
}

void ProcessorGraphic::pixelTransfer(){
    this->fetcher.tick();

    if(this->fetcher.hasPixel()){
        unsigned char pixelRaw = this->fetcher.popPixel();
        unsigned char pixel = (this->ram->get(Memory::BGP) >> ((uint8_t)pixelRaw * 2)) & 3;

        this->screen->write(pixel);
        this->x++;
    }

    if(this->x == 160){
        this->screen->HBlank();
        this->currentState = ProcessorGraphicState::HBlank;
    }
}

void ProcessorGraphic::hBlank(){
     if(this->ticks == 456){
        this->ticks = 0;
        this->ram->set(Memory::LY, this->ram->get(Memory::LY) + 1);

        if(this->ram->get(Memory::LY) == 144){
            this->screen->VBlank();
            this->currentState = ProcessorGraphicState::VBlank;
        }else{
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::vBlank(){
    if(this->ticks == 0){
        this->ram->requestInterupt(0); //set interruption vblank
    }
    
    if(this->ticks == 456){
        this->ticks = 0;
       this->ram->set(Memory::LY, this->ram->get(Memory::LY) + 1);

        if(this->ram->get(Memory::LY) == 153){
            this->ram->set(Memory::LY, 0);
            this->currentState = ProcessorGraphicState::OAMSearch;
        }
    }
}

void ProcessorGraphic::setLCDStatus(){
    unsigned char status = this->ram->get(Memory::LCD);
    int nextScanLineCounter = 456 - this->x; //quantity pixels left in scanline

    if (this->isLCDEnabled() == false){
        // set the mode to 1 during lcd disabled and reset scanline
        this->x = 0;
        this->ticks = 0;
        this->currentState = ProcessorGraphicState::OAMSearch;
        this->ram->writeMemory(Memory::LY, 0);
        status &= 0b11111100;
        setBit(status, 0);
        this->ram->writeMemory(Memory::LCD, status);
    }else{

        unsigned char currentline = this->ram->get(Memory::LY);
        unsigned char currentmode = status & 0b00000011;

        unsigned char mode = 0;
        bool reqInt = false;

        // in vblank so set mode to 1
        if (currentline >= 144){      
            mode = 1;
            setBit(status, 0);
            resetBit(status, 1);
            testBit(status, 4);
        }else{
            int mode2bounds = 456 - 80 ;
            int mode3bounds = mode2bounds - 172 ;

            // mode 2
            if (nextScanLineCounter >= mode2bounds){
                mode = 2 ;
                setBit(status, 1) ;
                resetBit(status, 0) ;
                reqInt = testBit(status, 5) ;
            }
            // mode 3
            else if(nextScanLineCounter >= mode3bounds){
                mode = 3 ;
                setBit(status, 1);
                setBit(status, 0);
            }
            // mode 0
            else{
                mode = 0;
                resetBit(status,1) ;
                resetBit(status,0) ;
                reqInt = testBit(status,3) ;
            }
        }

        // just entered a new mode so request interupt
        if (reqInt && (mode != currentmode))
                this->ram->requestInterupt(1);

        // check the conincidence flag
            if (currentline == this->ram->get(Memory::LYC)){
                setBit(status, 2) ;
                if (testBit(status, 6)){
                    this->ram->requestInterupt(1) ;
                }
        }else{
            resetBit(status, 2);
        }

        this->ram->writeMemory(Memory::LCD, status);
    }
}

bool ProcessorGraphic::isLCDEnabled(){
    return testBit(this->ram->get(Memory::LCDC), 7);
}

ProcessorGraphic::~ProcessorGraphic(){}