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



/*
 The majortiy of the code here is from an old project.
 */




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
    uint8 colorRG; //used for Launchpad Original, Mini, S and Mini MK2
    uint8 colorRGB[3]; //used for Pro and Launchpad RGB. Later will use for Push
    
    LFXColor ();
    LFXColor (uint8 r, uint8 g, uint8 b);
    
    void setRGB(uint8 r, uint8 g, uint8 b);
    void setRG (uint8 colorValue);
    void setRGBAndDowncastRG (uint8 r, uint8 g, uint8 b);
    void clearColor ();
    
    
    
    
    
};


static const LFXColor COLOFF () {
    LFXColor t(0,0,0);
    t.clearColor();
    return t;
}

static uint8 getRandomRGColor () {
#ifdef JUCE_MAC
    return colorsList[(arc4random() % eRGColorsTOTAL)];
#else 
    return colorsList[(arc4random() % eRGColorsTOTAL)];
#endif
}
#endif /* defined(__Crayon__LFXColor__) */
