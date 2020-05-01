//
//  OGDeviceLaunchpad.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "OGDeviceLaunchpad.hpp"


OGDeviceLaunchpad::OGDeviceLaunchpad (String MIDINameIn, String MIDINameOut) : OGDevice(MIDINameIn, MIDINameOut)
{
    jassert(hasConnectedOk());
    gridSize.x = 9;
    gridSize.y = 9;
    if (hasConnectedOk()) {
        resetDevice();
    }
    deviceName = MIDINameIn;
}
OGDeviceLaunchpad::~OGDeviceLaunchpad ()
{
    
}


void OGDeviceLaunchpad::setFeedback (LFXColor colour, XY position)
{
    position = getNeturalXY(position);
    
    // 8 is off
    // 00GG 10RR //
    
    /*
     We take the red and green components.
     red occupies the lowest two bits of the result.
     green occupies bits 4 and 5. (16 & 32)
     */
    const int red = colour.colorRGB[0];
    const int green = colour.colorRGB[1];
    const int colourRounded = (((red) / 85) + (((green) / 85) <<  4)) | 0x08;
    
    
    if (position.y == 0) {
        outDevice->sendMessageNow(MidiMessage::controllerEvent(1, 104+position.x, colourRounded));
    }
    else {
        outDevice->sendMessageNow(MidiMessage(0x90, position.x + ((position.y-1) * 16), colourRounded));
    }
}
const OGDevice::ePysicalRepresentation OGDeviceLaunchpad::getPysicalElementForXY (XY pos)
{
    pos = getNeturalXY(pos);
    if (pos.x == 8 && pos.y == 0) {
        return OGDevice::ePysicalRepresentation::eNone;
    }
    else if (pos.y == 0) {
        return OGDevice::ePysicalRepresentation::eRotary;
    }
    else if (pos.x == 8) {
        return OGDevice::ePysicalRepresentation::eRotary;
    }
    return OGDevice::ePysicalRepresentation::eSquareButton;
    
}
const OGDevice::eColourType OGDeviceLaunchpad::getColourType ()
{
    return OGDevice::eColourType::eRG;
}
void OGDeviceLaunchpad::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
 
    auto func = [this](int x, int y, int vel) {
            XY pos = {x,y};
            pos = getOrientatedXY(pos);
//            std::cout << pos.x << " - " << pos.y << " - " <<  vel << "\n";
//            setFeedback({}, pos);
        OGInMsg msg;
        msg.pos = pos;
        msg.type = eMomentryPad;
        msg.velocity = vel;
        if (callbackOGInMsg != nullptr) {
            callbackOGInMsg(msg, this);
        }
        
    };
 
    if (message.isNoteOnOrOff()) {
        if (message.isNoteOnOrOff()) {
            const int x = message.getNoteNumber() % 16;
            const int y = message.getNoteNumber() / 16 + 1;
            func(x,y,message.getVelocity());
        }
    }
    if (message.isController()) {
        const int num = message.getControllerNumber() - 104;
        func(num, 0, message.getControllerValue());
    }
    
}
void OGDeviceLaunchpad::resetDevice ()
{
    for (int i = 104; i < 104 + 8; i++) {
        outDevice->sendMessageNow(MidiMessage::controllerEvent(1, i, 0));
    }
    for (int i = 0; i < 127; i++) {
        outDevice->sendMessageNow(MidiMessage(0x90, i, 0));
    }
}
