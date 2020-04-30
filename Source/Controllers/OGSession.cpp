//
//  OGSession.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGSession.hpp"


OGSession::OGSession (OGDeviceManager & dm) : devManager(dm)
{
    devManager.createMap();
    
    auto size = devManager.getPadGridSize();
    controlerMap.resize(size.x * size.y);
    
}
OGSession::~OGSession ()
{
    
}

void OGSession::messageRecieved (OGDevice::OGInMsg msg)
{
    std::cout << "Message in og session! \n";
    
    devManager.testSendFeedback(msg.pos);
//    devManager.deviceForPadPosition(msg.pos)->setFeedback({}, <#XY position#>)
    //    const int index = pos.x + pos.y * padGridSize.x;
    //
    //    OGDevice * originalDevice = deviceMap[index].originalDevice;
    //
    //    originalDevice->setFeedback({}, {pos.x - originalDevice->offset.x, pos.y - originalDevice->offset.y} );
}
