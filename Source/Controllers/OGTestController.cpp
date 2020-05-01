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
    
}
OGTestController::~OGTestController ()
{
    
}
void OGTestController::messageRecieved (OGDevice::OGInMsg msg)
{
    LFXColor red{255,0,0};
    LFXColor off{0,0,0};
    
    lfxBuffer.writeToPositionXY(msg.velocity ? red : off, msg.pos.x, msg.pos.y);
    
    std::cout << msg.pos.x << " - " << msg.pos.y << "\n";
    
}
