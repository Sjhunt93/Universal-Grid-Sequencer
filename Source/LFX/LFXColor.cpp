//
//  LFXColor.cpp
//  Crayon
//
//  Created by Samuel Hunt on 23/07/2015.
//
//

#include "LFXColor.h"


void setRGB( LFXColor &color, u8 r, u8 g, u8 b)
{
    jassert(r < 64);
    jassert(g < 64);
    jassert(b < 64);
    color.colorRGB[RGBIndex::eRedIndex] = r;
    color.colorRGB[RGBIndex::eGreenIndex] = g;
    color.colorRGB[RGBIndex::eBlueIndex] = b;
}
void setRG (LFXColor &color, u8 colorValue)
{
    color.colorRG = colorValue;
}
void setRGBAndDowncastRG (LFXColor &color, u8 r, u8 g, u8 b)
{
    setRGB(color, r, g, b);
    
}
void clearColor (LFXColor &color)
{
    color.colorRGB[RGBIndex::eRedIndex] = 0;
    color.colorRGB[RGBIndex::eGreenIndex] = 0;
    color.colorRGB[RGBIndex::eBlueIndex] = 0;
    color.colorRG = 0;
}