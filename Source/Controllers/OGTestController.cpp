//
//  OGTestController.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 01/05/2020.
//
//

#include "OGTestController.hpp"

OGTestController::OGTestController (XY size, XY position) : OGController(size, position, OGController::eControllerList::eTest)
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
    
    sendMidi(MidiMessage::noteOn((uint8)1, (msg.pos.y * 16 + msg.pos.x) % 127, (uint8) msg.velocity), 0);
}

void OGTestController::clockPulse (int _1_4, int _1_8, int _1_16, int _1_32)
{
    const int x = arc4random() % size.x;
    const int y = arc4random() % size.y;
    const uint8 r = arc4random() % 256;
    const uint8 g = arc4random() % 256;
    lfxBuffer.writeToPositionXY({r,g,0}, x, y);
}
