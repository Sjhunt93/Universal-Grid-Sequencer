//
//  OGDeviceManager.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGDeviceManager.hpp"
#include "OGDeviceLaunchpad.hpp"

OGDeviceManager::OGDeviceManager (XY size) : gridSize(size)
{
    
}
OGDeviceManager::~OGDeviceManager ()
{
    for (int i = 0; i < devices.size(); i++) {
        delete devices[i];
    }
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
OGDevice * OGDeviceManager::deviceAtPos (XY pos)
{
    const int index = pos.x + pos.y * gridSize.x;
    if (index >= 0 && index < devices.size()) {
        return devices[index];
    }
    return nullptr;
}
void OGDeviceManager::deleteDevices (XY position)
{
    
}
void OGDeviceManager::messageRecieved (OGDevice * device, OGDevice::OGInMsg msg)
{
    XY pos = {device->offset.x + msg.pos.x, device->offset.y + msg.pos.y};
    std::cout << device->getDeviceName() << " - " << pos.x << " : " << pos.y << "\n";
    
    const int index = pos.x + pos.y * padGridSize.x;
    
    OGDevice * originalDevice = deviceMap[index].originalDevice;
    
    originalDevice->setFeedback({}, {pos.x - originalDevice->offset.x, pos.y - originalDevice->offset.y} );
    
    
//    deviceMap[index].originalDevice->setFeedback({}, <#XY position#>)

    
}
void OGDeviceManager::createMap ()
{
    int xSize = 0;
    int ySize = 0;
    
    for (int i = 0; i < gridSize.x; i++) {
        xSize += deviceAtPos({i, 0})->getTotalGridSize().x;
    }
    for (int i = 0; i < gridSize.y; i++) {
        ySize += deviceAtPos({0, i})->getTotalGridSize().y;
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
    
    
}
