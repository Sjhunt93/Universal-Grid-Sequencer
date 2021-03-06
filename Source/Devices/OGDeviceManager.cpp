//
//  OGDeviceManager.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGDeviceManager.hpp"
#include "OGDeviceLaunchpad.hpp"
#include "OGSession.hpp"
#include "OGController.hpp"

OGDeviceManager::OGDeviceManager (XY size) : gridSize(size) //, deviceBufferSend(1,1)
{
    deviceBufferSend = nullptr;
    
    deviceOutput = MidiOutput::createNewDevice("Open Grid Midi Out");
    
}
OGDeviceManager::~OGDeviceManager ()
{
    for (int i = 0; i < devices.size(); i++) {
        delete devices[i];
    }
    delete deviceBufferSend;
}

void OGDeviceManager::createNewDevice (eDeviceType type, XY position, String midiIn, String midiOut)
{
    switch (type) {
        case eLaunchpadRG:
        {
            OGDevice * device = new OGDeviceLaunchpad(midiIn, midiOut);
            devices.push_back(device);
            device->callbackOGInMsg = [this](OGDevice::OGInMsg msg, OGDevice * device)
            {
                messageRecieved(device, msg);
            };
        }
            break;
        default:
            break;
    }
}
OGDevice * OGDeviceManager::deviceAtPosInVector (XY pos)
{
    const int index = pos.x + pos.y * gridSize.x;
    if (index >= 0 && index < devices.size()) {
        return devices[index];
    }
    return nullptr;
}

OGDevice * OGDeviceManager::deviceForPadPosition (XY pos)
{
    const int index = pos.x + pos.y * padGridSize.x;
    if (index < deviceMap.size()) {
        OGDevice * originalDevice = deviceMap[index].originalDevice;
        return originalDevice;
    }
    
    return nullptr;
}

const XY OGDeviceManager::getPadGridSize ()
{
    return padGridSize;
}
void OGDeviceManager::deleteDevices (XY position)
{
    
}
void OGDeviceManager::messageRecieved (OGDevice * device, OGDevice::OGInMsg msg)
{
    XY pos = {device->offset.x + msg.pos.x, device->offset.y + msg.pos.y};
//    std::cout << device->getDeviceName() << " - " << pos.x << " : " << pos.y << "\n";
    
    //translate
    msg.pos = pos; //update the position
    messageBuffer.addMessage(msg);
    
    
//    const int index = pos.x + pos.y * padGridSize.x;
//    
//    OGDevice * originalDevice = deviceMap[index].originalDevice;
//    
//    originalDevice->setFeedback({}, {pos.x - originalDevice->offset.x, pos.y - originalDevice->offset.y} );
//    
    
//    deviceMap[index].originalDevice->setFeedback({}, <#XY position#>)

    
    
    
}
void  OGDeviceManager::testSendFeedback (XY pos)
{
    const int index = pos.x + pos.y * padGridSize.x;
    OGDevice * originalDevice = deviceMap[index].originalDevice;
    
    originalDevice->setFeedback({}, {pos.x - originalDevice->offset.x, pos.y - originalDevice->offset.y} );
}
void OGDeviceManager::createMap ()
{
    int xSize = 0;
    int ySize = 0;
    
    for (int i = 0; i < gridSize.x; i++) {
        xSize += deviceAtPosInVector({i, 0})->getTotalGridSize().x;
    }
    for (int i = 0; i < gridSize.y; i++) {
        ySize += deviceAtPosInVector({0, i})->getTotalGridSize().y;
    }
    const int totalSize = xSize * ySize;
    padGridSize.x = xSize;
    padGridSize.y = ySize;

    deviceMap.clear();
    deviceMap.resize(totalSize);

    for (auto * device : devices) {
        XY offset = device->offset;
        for (int x = 0; x < device->getTotalGridSize().x; x++) {
            for (int y = 0; y < device->getTotalGridSize().y; y++) {
                const int xM = x+offset.x;
                const int yM = y+offset.y;
                
                const int index = xM + yM * ySize;
                deviceMap[index].originalDevice = device;
                deviceMap[index].index = index;
                deviceMap[index].pos = {xM, yM};
                
            }
        }
        
    }
    
    delete deviceBufferSend;
    deviceBufferSend = new LFXBuffer(padGridSize.y, padGridSize.x);
}
void OGDeviceManager::dispatchBufferToControllers (OGSession * sessionToSendToo)
{
    //technically sessionToSendToo can be a nullptr, which means that we just use this to clear the buffer..
    
    int size = messageBuffer.clearBuffer(messageBufferLocal);
    if (sessionToSendToo == nullptr) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        sessionToSendToo->messageRecieved(messageBufferLocal[i]);
    }
}

void OGDeviceManager::collectLFXBuffers (OGSession * session)
{
    if (session != nullptr) {
        for (int ci = 0; ci < session->getTotalControllers(); ci++) {
            auto controller = session->controllerForIndex(ci);
            jassert(controller != nullptr);
            
            LFXBuffer & bufferToCopy = controller->getLFXBuffer();
            for (int x = 0; x < bufferToCopy.totalColums; x++) {
                for (int y = 0; y < bufferToCopy.totalRows; y++) {
                    XY posRelativeToGrid = {x+controller->position.x, y+controller->position.y}; //overall grid
                    
                    bool toSend = deviceBufferSend->writeOptimised(bufferToCopy.colorForPostion(y, x), posRelativeToGrid.x, posRelativeToGrid.y);
                    
                   if (toSend) {
                        //we need to now send.
                        const int index = posRelativeToGrid.x + posRelativeToGrid.y * padGridSize.x;
                    
                        OGDevice * originalDevice = deviceMap[index].originalDevice;
                        originalDevice->setFeedback(deviceBufferSend->colorForPostion(posRelativeToGrid.y, posRelativeToGrid.x), {posRelativeToGrid.x - originalDevice->offset.x, posRelativeToGrid.y - originalDevice->offset.y} );
//                    originalDevice->setFeedback(deviceBufferSend->colorForPostion(y, x), {posRelativeToGrid.x, posRelativeToGrid.y} );
                       
                    }
                    
                }
            }
        }
    }
}


void OGDeviceManager::sendMidiMessageMaster (MidiMessage m)
{
    if (deviceOutput != nullptr) {
        deviceOutput->sendMessageNow(m);
    }
}
