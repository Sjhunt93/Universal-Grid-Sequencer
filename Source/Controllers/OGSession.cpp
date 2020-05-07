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
#include "OGControllerLargeDrumPad.hpp"
#include "OGControllerMediumDrumPad.hpp"

OGSession::OGSession (OGDeviceManager & dm) : devManager(dm)
{
    devManager.createMap();
    
    auto size = devManager.getPadGridSize();
    controlerMap.resize(size.x * size.y);
    
    //OGControllerLargeDrumPad * controller = new OGControllerLargeDrumPad({16,16}, {1,1});
    
    OGControllerMediumDrumPad * controller = new OGControllerMediumDrumPad({8,8}, {1,1});
    
//    OGTestController * controller = new OGTestController({5,5}, {6,6});
    controller->sendMidiOutput = [this](MidiMessage m)
    {
        devManager.sendMidiMessageMaster(m);
    };
    controllers.push_back(controller);
    buildMap();
    
    
}
OGSession::~OGSession ()
{
    
}

void OGSession::buildMap ()
{
    
    for (auto & m : controlerMap) {
        m.controller = nullptr;
    }
    
    for (int i = 0; i < controllers.size(); i++) {
        
        XY size = controllers[i]->size;
        XY position = controllers[i]->position;
        for (int x = 0; x < size.x; x++) {
            for (int y = 0; y < size.y; y++) {
                const int xPos = x + position.x;
                const int yPos = y + position.y;
                
                const int index = xPos + yPos * devManager.getPadGridSize().y;
                controlerMap[index].controller = controllers[i];
                controlerMap[index].pos = {0,0};
            }
        }
        
    }
}

void OGSession::messageRecieved (OGDevice::OGInMsg msg)
{
    
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
