#include "ProcessorGraphic.h"

ProcessorGraphic::ProcessorGraphic(){
    this->VBlankTick = 0;
    this->x = 0;
    this->ticks = 0;
    this->LY = 0; //TODO maybe take this value in the memory
}

void ProcessorGraphic::tick(){
    switch (this->currentState){
        case ProcessorGraphicState::OAMSearch:
            this->collectSprite();
            this->currentState = ProcessorGraphicState::PixelTransfer;
            break;

        case ProcessorGraphicState::PixelTransfer:
            this->drawLine();
            this->currentState = ProcessorGraphicState::HBlank;
            break;

        case ProcessorGraphicState::HBlank:
            if(this->ticks == 456){
                this->ticks = 0;
                this->LY++;

                if(this->LY == 144){
                    this->currentState = ProcessorGraphicState::VBlank;
                }else{
                    this->currentState = ProcessorGraphicState::OAMSearch;
                }
            }
            break;

        case ProcessorGraphicState::VBlank:
            if(this->VBlankTick == 10){
                this->VBlankTick = 0;

                if(this->ticks == 456){
                this->ticks = 0;
                this->LY++;

                if(this->LY == 153){
                    this->LY = 0;
                    this->currentState = ProcessorGraphicState::OAMSearch;
                }
            }else{
                this->VBlankTick++;
            }

            break;
            }

        default:
            break;
    }

    this->ticks++;
}

void ProcessorGraphic::drawLine(){
    // TODO: Fetch pixel data into our pixel FIFO.
    // TODO: Put a pixel (if any) from the FIFO on screen.
    // Check when the scanline is complete (160 pixels).

    if(this->x == 160){
        this->currentState = ProcessorGraphicState::HBlank;
    }
}

void ProcessorGraphic::collectSprite(){
    // In this state, the PPU would scan the OAM (Objects Attribute Memory)
    // from 0xfe00 to 0xfe9f to mix sprite pixels in the current line later.
    // This always takes 40 ticks.

    if(this->ticks == 40){
        this->currentState = ProcessorGraphicState::PixelTransfer;
    }
}