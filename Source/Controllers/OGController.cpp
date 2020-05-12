//
//  OGController.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 30/04/2020.
//
//

#include "OGController.hpp"


OGController::OGController (XY s, XY p, const eControllerList t) : size(s), position(p), type(t), lfxBuffer(size.y, size.x), bufferHelper(lfxBuffer)
{
    colorList.resize(1);
}
OGController::~OGController ()
{
    
}

void OGController::setup (const int noteMapSize)
{
    colorList.resize(getColoursRequired());
    externalControlValues.resize(getNumberOfExternalControls());
    noteMap.values.resize(noteMapSize);
    
    for (auto & a : externalControlValues) {
        a = 0;
    }
    
    externalControlValues[eOctave] = 4;
    externalControlValues[eRelease] = 300;
    externalControlValues[eStartNote] = 36;
    externalControlValues[eOveralp] = 4;
    
    
    
}

LFXBuffer& OGController::getLFXBuffer ()
{
    return lfxBuffer;
}
OGController::NoteMap & OGController::getNoteMap ()
{
    return noteMap;
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
void OGController::sendMidi (MidiMessage m, int delay)
{
    if (sendMidiOutput != nullptr) {
        sendMidiOutput(m, delay);
    }
}
void OGController::sendControl (ControlMessage control)
{
    if (sendControlMessage != nullptr) {
        sendControlMessage(control);
    }
}
void OGController::setExternalControl (const int index, int value)
{
    if (index <= externalControlValues.size() && index >= 0) {
        externalControlValues[index] = value;
    }
    refresh();
}

/*static*/ OGController * OGController::allocateForType (eControllerList type)
{
    switch (type) {
        case eTest:
            
            break;
            
        default:
            break;
    }
}
