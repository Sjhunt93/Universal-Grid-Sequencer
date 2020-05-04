//
//  OGTestController.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 01/05/2020.
//
//

#include "OGTestController.hpp"

OGTestController::OGTestController (XY size, XY position) : OGController(size, position)
{
    setup();
    
    LFXColor red{255,0,0};
    setColour(red, 0);
}
OGTestController::~OGTestController ()
{
    
}
void OGTestController::messageRecieved (OGDevice::OGInMsg msg)
{
    
    LFXColor off{0,0,0};
    
    lfxBuffer.writeToPositionXY(msg.velocity ? getColour(0) : off, msg.pos.x, msg.pos.y);
    
    std::cout << msg.pos.x << " - " << msg.pos.y << "\n";
    
    sendMidi(MidiMessage::noteOn((uint8)1, (msg.pos.y * 16 + msg.pos.x) % 127, (uint8) msg.velocity));
}
