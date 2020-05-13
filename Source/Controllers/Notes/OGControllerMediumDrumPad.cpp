//
//  OGControllerMediumDrumPad.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 07/05/2020.
//
//

#include "OGControllerMediumDrumPad.hpp"


OGControllerMediumDrumPad::OGControllerMediumDrumPad (XY size, XY position) : OGController(size, position, OGController::eControllerList::eDrumLargePad)
{
    
    setup();
    setColour(LFXColor(125, 0, 0), 0);
    setColour(LFXColor(125, 125, 0), 1);
    setColour(LFXColor(255, 125, 0), 2);
    setColour(LFXColor(255, 255, 0), 3);
    
    customColours[0] = LFXColor(255, 255, 0); //yellows
    customColours[1] = LFXColor(170, 170, 0);
    customColours[2] = LFXColor(85, 85, 0);
    customColours[3] = LFXColor(170, 170, 0);
    
    customColours[4] = LFXColor(0, 255, 0); //greens
    customColours[5] = LFXColor(0, 170, 0);
    customColours[6] = LFXColor(0, 170, 0);
    customColours[7] = LFXColor(0, 85, 0);
    
    customColours[8] = LFXColor(85, 0, 0); //red
    customColours[9] = LFXColor(85, 255, 0); //mixed
    customColours[10] = LFXColor(255, 170, 0); //orange
    customColours[11] = LFXColor(255, 170, 0); //mixed
    
    customColours[12] = LFXColor(85, 0, 0); //red
    customColours[13] = LFXColor(85, 255, 0); //mixed
    customColours[14] = LFXColor(170, 170, 0); //yellow mid
    customColours[15] = LFXColor(255, 255, 0); //yellow max
    
    //    colGrenYel  =   57, //0011 1001

    useCustomColours = true;
    
    refresh();

    
    
}
OGControllerMediumDrumPad::~OGControllerMediumDrumPad ()
{
    
}

void OGControllerMediumDrumPad::messageReceived (OGDevice::OGInMsg msg)
{
    
    const int xM = msg.pos.x / 2;
    const int yM = msg.pos.y / 2;
    
    //    static uint8 drumMap[]
    
    
    static uint8 velocityMap[] = {
        16,
        48,
        96,
        127,
    };
    
    int velocityIndex = (msg.pos.x % 2) + ((msg.pos.y  % 2) * 2);
    const uint8 velOut = msg.velocity ? velocityMap[velocityIndex] : 0;
    
    const int noteIndex = (xM) + ((yM) * 4);
    
    //lfxBuffer.wri
    //fix to be eChannel
    const MidiMessage message = MidiMessage::noteOn((uint8) 1, noteValues[noteIndex], velOut); //stupid (uint8) casts to remove ambigious warning
    
    sendMidi(message, 0);
    
    if (useCustomColours) {
        bufferHelper.drawSquare(xM*2, yM*2, 2, 2,  msg.velocity ? LFXColor(255, 0, 0) : customColours[noteIndex]);
    }
    else {
        bufferHelper.drawSquare(xM*2, yM*2, 2, 2,  getColour( msg.velocity ? ((xM+yM) % 2) + 2 : (xM+yM) % 2));
    }
    //lfxBuffer.writeToPositionXY(getColour(3), msg.pos.x, msg.pos.y);
}
XY OGControllerMediumDrumPad::getMinimumSize ()
{
    return {2,2};
}
XY OGControllerMediumDrumPad::getMaximumSize ()
{
    return {16,16};
}
void OGControllerMediumDrumPad::refresh ()
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (useCustomColours) {
                bufferHelper.drawSquare(x*2, y*2, 2, 2,  customColours[x+y*4]);
            }
            else {
            bufferHelper.drawSquare(x*2, y*2, 2, 2,  getColour((x+y) % 2));
            }
            
        }
    }
}
const int OGControllerMediumDrumPad::getColoursRequired ()
{
    return 4;
}

std::array<uint8, 16> & OGControllerMediumDrumPad::getNoteValues ()
{
    return noteValues;
}

std::array<LFXColor, 16> & OGControllerMediumDrumPad::getColourValues ()
{
    useCustomColours = true;
    return customColours;
}

//useCustomColours
