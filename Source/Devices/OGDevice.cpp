//
//  OGDevice.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGDevice.hpp"


OGDevice::OGDevice (String MIDINameIn, String MIDINameOut)
{
    auto arrayIn = MidiInput::getAvailableDevices();
    for (auto device : arrayIn) {
        if (device.name == MIDINameIn) {
            inDevice = MidiInput::openDevice(device.identifier, this);
            inDevice->start();
        }
    }
    
    auto arrayOut = MidiOutput::getAvailableDevices();
    for (auto device : arrayOut) {
        if (device.name == MIDINameOut) {
            outDevice = MidiOutput::openDevice(device.identifier);
        }
    }
    jassert(inDevice != nullptr);
    jassert(outDevice != nullptr);
    if (hasConnectedOk()) {
        inDevice->start();    
    }
    offset = {0,0};
    
}
OGDevice::~OGDevice ()
{
    inDevice = nullptr;
    outDevice = nullptr;
}

void OGDevice::setOrientation (eOrientation orientation)
{
    currentOrientation = orientation;
}
const XY OGDevice::getTotalGridSize ()
{
    return gridSize;
}
const String OGDevice::getDeviceName ()
{
    return deviceName;
}
const bool OGDevice::hasConnectedOk ()
{
    return (inDevice != nullptr) && (outDevice != nullptr);
}

XY OGDevice::getNeturalXY (XY position)
{
    XY transfer = position;
    if (currentOrientation == eRotatedRight) {
        transfer.x = position.y;
        transfer.y = (gridSize.x-1) - position.x;
    }
    else if (currentOrientation == eRotated180) {
        
        transfer.x = (gridSize.x-1) - position.x;
        transfer.y = (gridSize.y-1) - position.y;
    }
    else if (currentOrientation == eRotatedLeft) {
        transfer.y = position.x;
        transfer.x = (gridSize.y-1) - position.y;
    }
    return transfer;
}
XY OGDevice::getOrientatedXY (XY position)
{
    XY transfer = position;
    if (currentOrientation == eRotatedLeft) {
        transfer.x = position.y;
        transfer.y = (gridSize.x-1) - position.x;
    }
    else if (currentOrientation == eRotated180) {
        
        transfer.x = (gridSize.x-1) - position.x;
        transfer.y = (gridSize.y-1) - position.y;
    }
    else if (currentOrientation == eRotatedRight) {
        transfer.y = position.x;
        transfer.x = (gridSize.y-1) - position.y;
    }
    return transfer;
}
