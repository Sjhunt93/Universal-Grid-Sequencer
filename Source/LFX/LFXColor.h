//
//  LFXColor.h
//  Crayon
//
//  Created by Samuel Hunt on 23/07/2015.
//
//

#ifndef __Crayon__LFXColor__
#define __Crayon__LFXColor__

#include "../JuceLibraryCode/JuceHeader.h"


typedef unsigned char u8; //default for MIDI


enum RGBIndex {
    eRedIndex = 0,
    eGreenIndex,
    eBlueIndex,
};


typedef enum eRGDeviceColors
{
    colOff      =   8,
    colGreen1   =   24,
    colGreen2   =   40,
    colGreen3   =   56,
    colRed1     =   9,
    colRed2     =   10,
    colRed3     =   11,
    colYel1     =   25,
    colYel2     =   45,
    colYel3     =   59,
    colOran1    =   43,
    colOran2    =   26,
    colOran3    =   27,
    colGrenYel  =   57,
    colGold     =   58,
    eRGColorsTOTAL  = 14,
    
}eRGDeviceColors;

static const eRGDeviceColors colorsList[] = {colGreen1, colGreen2, colGreen3, colRed1, colRed2, colRed3, colYel1, colYel2, colYel3, colOran1, colOran2, colOran3, colGrenYel, colGold};

//for pure efficent we want to keep any functionality outside of LPFXColor, as we will have buffers and buffers of these small LFXcolors etc...

struct LFXColor {
    u8 colorRG; //used for Launchpad Original, Mini, S and Mini MK2
    u8 colorRGB[3]; //used for Pro and Launchpad RGB. Later will use for Push
};

void setRGB( LFXColor &color, u8 r, u8 g, u8 b);
void setRG (LFXColor &color, u8 colorValue);
void setRGBAndDowncastRG (LFXColor &color, u8 r, u8 g, u8 b);
void clearColor (LFXColor &color);

static const LFXColor COLOFF () {
    LFXColor t;
    clearColor(t);
    return t;
}

static u8 getRandomRGColor () {
#ifdef JUCE_MAC
    return colorsList[(arc4random() % eRGColorsTOTAL)];
#else 
    return colorsList[(arc4random() % eRGColorsTOTAL)];
#endif
}
#endif /* defined(__Crayon__LFXColor__) */
