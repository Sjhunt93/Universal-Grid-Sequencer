//
//  OGControllerNoteScaleRepeater.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 12/05/2020.
//
//

#include "OGControllerNoteScaleRepeater.hpp"
#include "Scales.h"

OGControllerNoteScaleRepeater::OGControllerNoteScaleRepeater (XY size, XY position) : OGController(size, position, OGController::eControllerList:: eNoteScaleRepeater)
{
    
    noteMap.resize(size.x * size.y);
    
    setup();
    setColour(LFXColor(125, 0, 0), 0);
    setColour(LFXColor(125, 125, 0), 1);
    setColour(LFXColor(255, 125, 0), 2);
    refresh();
}
OGControllerNoteScaleRepeater::~OGControllerNoteScaleRepeater ()
{
    
}

void OGControllerNoteScaleRepeater::messageRecieved (OGDevice::OGInMsg msg)
{
    
//    const int note =
//    const int scalePosition = msg.pos.x % scaleLen; + y * octave;
    
    const int index = msg.pos.x + msg.pos.y * size.y;
    const int note = noteMap[index].note;
    if (note >= 0 && note < 128) {
        sendMidi(MidiMessage::noteOn(1, (uint8)note, (uint8)msg.velocity), 0);
        
        if (msg.velocity) {
            lfxBuffer.writeToPositionXY(getColour(2), msg.pos.x, msg.pos.y);
        }
        else {
            if (noteMap[index].note % 12 == 0) {
                lfxBuffer.writeToPositionXY(getColour(0), msg.pos.x, msg.pos.y);
            }
            else {
                
                if (noteMap[index].isInScale) {
                    lfxBuffer.writeToPositionXY(getColour(1), msg.pos.x, msg.pos.y);
                }
                else {
                    lfxBuffer.writeToPositionXY({}, msg.pos.x, msg.pos.y);
                }
            }
            
        }
    }
}
XY OGControllerNoteScaleRepeater::getMinimumSize ()
{
    return {1,1};
}
XY OGControllerNoteScaleRepeater::getMaximumSize ()
{
    return {16,16};
}
void OGControllerNoteScaleRepeater::refresh ()
{
    //setup scale
    const int overlap = externalControlValues[OGController::eExternalControlIndexes::eOveralp];
    const int root = externalControlValues[OGController::eExternalControlIndexes::eStartNote];
    const int scale = externalControlValues[OGController::eExternalControlIndexes::eScale];
    
    const uint8  * localScalePtr;
    uint8 localLen = 0;
    pointToScale(scale, &localScalePtr, &localLen);
    
    
    auto checkScale = [&](int note) -> bool
    {
        const int pitch = note % 12;
        for (int i = 0; i < localLen; i++) {
            if (localScalePtr[i] == pitch) {
                return true;
            }
        }
        return false;
    };
    
    for (int y = 0; y < size.y; y++) {
        
        
        const int startNote = root + overlap*y;
        
        for (int x = 0; x < size.x; x++) {
            const int writeY = (size.y-1) - y;
            const int index = writeY * size.x + x;
            
            noteMap[index].note = startNote+x;
            noteMap[index].isInScale = checkScale(noteMap[index].note);
            
            if (noteMap[index].note >= 0 && noteMap[index].note < 128) {
                if (noteMap[index].note % 12 == 0) {
                    lfxBuffer.writeToPositionXY(getColour(0), x, y);
                }
                else {
                    
                    if (noteMap[index].isInScale) {
                        lfxBuffer.writeToPositionXY(getColour(1), x, y);
                    }
                    else {
                        lfxBuffer.writeToPositionXY({}, x, y);
                    }
                }
            }
            
            
        }
        
    }
}
const int OGControllerNoteScaleRepeater::getColoursRequired ()
{
    return 3;
}
