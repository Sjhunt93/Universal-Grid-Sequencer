//
//  LFXColor.cpp
//  Crayon
//
//  Created by Samuel Hunt on 23/07/2015.
//
//

#include "LFXColor.h"

LFXColor::LFXColor ()
{
    clearColor();
}
LFXColor::LFXColor (uint8 r, uint8 g, uint8 b)
{
    colorRGB[RGBIndex::eRedIndex] = r;
    colorRGB[RGBIndex::eGreenIndex] = g;
    colorRGB[RGBIndex::eBlueIndex] = b;
}

void LFXColor::setRGB(uint8 r, uint8 g, uint8 b)
{
    jassert(r < 64);
    jassert(g < 64);
    jassert(b < 64);
    colorRGB[RGBIndex::eRedIndex] = r;
    colorRGB[RGBIndex::eGreenIndex] = g;
    colorRGB[RGBIndex::eBlueIndex] = b;
}
void LFXColor::setRG (uint8 colorValue)
{
    colorRG = colorValue;
}
void LFXColor::setRGBAndDowncastRG (uint8 r, uint8 g, uint8 b)
{
    setRGB(r, g, b);
    
}
void LFXColor::clearColor ()
{
    colorRGB[RGBIndex::eRedIndex] = 0;
    colorRGB[RGBIndex::eGreenIndex] = 0;
    colorRGB[RGBIndex::eBlueIndex] = 0;
    colorRG = 0;
}
