//
//  OGController.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 30/04/2020.
//
//

#include "OGController.hpp"


OGController::OGController (XY s, XY p) : size(s), position(p), lfxBuffer(size.x, size.y)
{
    colorList.resize(1);
    externalControlValues.resize(eExternalCustomStart+36);
}
OGController::~OGController ()
{
    
}

void OGController::setup ()
{
    colorList.resize(getColoursRequired());
}

LFXBuffer& OGController::getLFXBuffer ()
{
    return lfxBuffer;
}


void OGController::setColour (LFXColor col, const int index)
{
    colorList[index] = col;
}
LFXColor OGController::getColour (const int index)
{
    jassert(index >= 0 && index <= colorList.size());
    return colorList[index];
}
void OGController::sendMidi (MidiMessage m)
{
    if (sendMidiOutput != nullptr) {
        sendMidiOutput(m);
    }
}
void OGController::setExternalControl (const int index, int value)
{
    if (index <= externalControlValues.size() && index >= 0) {
        externalControlValues[index] = value;
    }
}
