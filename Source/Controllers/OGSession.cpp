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
#include "OGControllerSequencerSimple.hpp"

OGSession::OGSession (OGDeviceManager & dm, MasterClock & clock) : devManager(dm), mClock(clock)
{
    devManager.createMap();
    
    auto size = devManager.getPadGridSize();
    controlerMap.resize(size.x * size.y);
    

    overlap = 4;
    

    
    
}
OGSession::~OGSession ()
{
    for (int i = 0; i < controllers.size(); i++) {
        delete controllers[i];
    }
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
    
    if (msg.pos.y == 0 && msg.velocity)
    {
        if (msg.pos.x == 1) {
            mClock.setTransportForAllClocks(Clock::ePlay);
        }
        else if (msg.pos.x == 2) {
            mClock.setTransportForAllClocks(Clock::ePause);
        }
        else if (msg.pos.x == 3) {
            mClock.setTransportForAllClocks(Clock::eRestart);
            for (int i = 0; i < controllers.size(); i++) {
                OGControllerSequencerRoot * seq = dynamic_cast<OGControllerSequencerRoot *>(controllers[i]);
                if (seq != nullptr) {
                    seq->restartSequence();
                }
            }
            //
        }
        else if (msg.pos.x == 4 || msg.pos.x == 5) {
            if (msg.pos.x == 4) {
                overlap--;
                if (overlap < 1) {
                    overlap = 1;
                }
            }
            else {
                overlap++;
                if (overlap > 12) {
                    overlap = 12;
                }
            }
            for (int i = 0; i < controllers.size(); i++) {
                controllers[i]->setExternalControl(OGController::eExternalControlIndexes::eOveralp, overlap);
                
            }
        }
        
        
    }
    else {
        const int index = msg.pos.x + msg.pos.y * devManager.getPadGridSize().x;
        
        if (controlerMap[index].controller != nullptr) {
            //send on to the controller...
            msg.pos.x = msg.pos.x - controlerMap[index].controller->position.x;
            msg.pos.y = msg.pos.y - controlerMap[index].controller->position.y;
            controlerMap[index].controller->messageRecieved(msg);
        }
    }
    
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
void OGSession::addNewController (OGController * controller)
{
    controller->sendMidiOutput = [this](MidiMessage m, int delay)
    {
        if (delay > 0) {
            mClock.queMidiMessage(m, delay);
        }
        else {
            devManager.sendMidiMessageMaster(m);
        }
        
    };
    
    controller->sendControlMessage = [this](OGController::ControlMessage c)
    {
        this->sendControlMessages(c);
    };
    
    controllers.push_back(controller);
    buildMap();
}
void OGSession::sendControlMessages (OGController::ControlMessage)
{
    
}
