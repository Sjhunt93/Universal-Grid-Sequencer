//
//  OGControllerLargeDrumPad.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 04/05/2020.
//
//

#include "OGControllerLargeDrumPad.hpp"



OGControllerLargeDrumPad::OGControllerLargeDrumPad (XY size, XY position) : OGController(size, position), bufferHelper(lfxBuffer)
{
    setup();
    setColour(LFXColor(125, 0, 0), 0);
    setColour(LFXColor(125, 125, 0), 1);
    setColour(LFXColor(255, 125, 0), 2);
    setColour(LFXColor(255, 255, 0), 3);
    refresh();
    
}
OGControllerLargeDrumPad::~OGControllerLargeDrumPad ()
{

}
void OGControllerLargeDrumPad::messageRecieved (OGDevice::OGInMsg msg)
{
    const int xM = msg.pos.x / 4;
    const int yM = msg.pos.y / 4;
    
    std::cout << msg.pos.x << " : " << msg.pos.y << "\n";
    
    static uint8 drumMap[] = {57,49,51,53,48,47,45,43,36,40,37,39,36,40,42,46};

    
    static uint8 velocityMap[] = {
        8,16,24,32,
        40,48,56,64,
        72,80,88,96,
        104,112,120,127,
    };
    
    int velocityIndex = (msg.pos.x % 4) + ((msg.pos.y  % 4) * 4);
    const uint8 velOut = msg.velocity ? velocityMap[velocityIndex] : 0;
    
    const int noteIndex = (msg.pos.x / 4) + ((msg.pos.y / 4) * 4);
    
    //lfxBuffer.wri
    //fix to be eChannel
    const MidiMessage message = MidiMessage::noteOn((uint8) 1, drumMap[noteIndex], velOut); //stupid (uint8) casts to remove ambigious warning
    
    sendMidi(message);
    
    bufferHelper.drawSquare(xM*4, yM*4, 4, 4,  getColour( msg.velocity ? ((xM+yM) % 2) + 2 : (xM+yM) % 2));
    //lfxBuffer.writeToPositionXY(getColour(3), msg.pos.x, msg.pos.y);

}
XY OGControllerLargeDrumPad::getMinimumSize ()
{
    return {4,4};
}
XY OGControllerLargeDrumPad::getMaximumSize ()
{
    return {16,16};
}
void OGControllerLargeDrumPad::refresh ()
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            const int sum = x + y * 4;
            bufferHelper.drawSquare(x*4, y*4, 4, 4,  getColour((x+y) % 2));
            
        }
    }
}
const int OGControllerLargeDrumPad::getColoursRequired ()
{
    return 4;
}
