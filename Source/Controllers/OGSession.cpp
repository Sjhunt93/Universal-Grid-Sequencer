//
//  OGSession.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGSession.hpp"
#include "OGController.hpp"
#include "OGTestController.hpp"

OGSession::OGSession (OGDeviceManager & dm) : devManager(dm)
{
    devManager.createMap();
    
    auto size = devManager.getPadGridSize();
    controlerMap.resize(size.x * size.y);
    
    OGTestController * controller = new OGTestController(devManager.getPadGridSize(), {0,0});
    controllers.push_back(controller);
    buildMap();
    
    
}
OGSession::~OGSession ()
{
    
}

void OGSession::buildMap ()
{
    for (int i = 0; i < controllers.size(); i++) {
        
        XY size = controllers[i]->size;
        for (int x = 0; x < size.x; x++) {
            for (int y = 0; y < size.y; y++) {
                const int index = x + y * devManager.getPadGridSize().y;
                controlerMap[index].controller = controllers[i];
                controlerMap[index].pos = {0,0};
            }
        }
        
    }
}

void OGSession::messageRecieved (OGDevice::OGInMsg msg)
{
    std::cout << "Message in og session! \n";
    
    devManager.testSendFeedback(msg.pos);
    
    const int index = msg.pos.x + msg.pos.y * devManager.getPadGridSize().x;
    
    if (controlerMap[index].controller != nullptr) {
        //send on to the controller...
        msg.pos.x = msg.pos.x - controlerMap[index].controller->position.x;
        msg.pos.y = msg.pos.y - controlerMap[index].controller->position.y;
        controlerMap[index].controller->messageRecieved(msg);
    }
    
//    devManager.deviceForPadPosition(msg.pos)->setFeedback({}, <#XY position#>)
    //
    //
    //    OGDevice * originalDevice = deviceMap[index].originalDevice;
    //
    //    originalDevice->setFeedback({}, {pos.x - originalDevice->offset.x, pos.y - originalDevice->offset.y} );
}

const int OGSession::getTotalControllers ()
{
    return controllers.size();
}
OGController * OGSession::controllerForIndex (const int index)
{
    if (index >= 0 && index <= getTotalControllers()) {
        return controllers[index];
    }
    return nullptr;
    
    
}
