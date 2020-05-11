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
 The majortiy of the code here is from an old project. crayon
 */




enum RGBIndex {
    eRedIndex = 0,
    eGreenIndex,
    eBlueIndex,
};


typedef enum eRGDeviceColors
{
    colOff      =   8,
    colGreen1   =   24, //0001 1000
    colGreen2   =   40, //0010 1000
    colGreen3   =   56, //0011 1000
    colRed1     =   9,  //0000 1001
    colRed2     =   10, //0000 1010
    colRed3     =   11, //0000 1011
    colYel1     =   25, //0001 1001
    colYel2     =   41, //0010 1001
    colYel3     =   59, //0011 1011
    colOran1    =   43, //0010 1011
    colOran2    =   26, //0001 1010
    colOran3    =   27, //0001 1011
    colGrenYel  =   57, //0011 1001
    colGold     =   58, //0011 1010
    eRGColorsTOTAL  = 14,
    
}eRGDeviceColors;

static const eRGDeviceColors colorsList[] = {colGreen1, colGreen2, colGreen3, colRed1, colRed2, colRed3, colYel1, colYel2, colYel3, colOran1, colOran2, colOran3, colGrenYel, colGold};

//for pure efficent we want to keep any functionality outside of LPFXColor, as we will have buffers and buffers of these small LFXcolors etc...

struct LFXColor {
    uint8 colorRG; //used for Launchpad Original, Mini, S and Mini MK2
    uint8 colorRGB[3]; //used for Pro and Launchpad RGB. Later will use for Push
    bool alphaEnabled = true; //disable the alpha so that when this is used in the buffer later on, any buffer transfers are ingnored.
    
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
