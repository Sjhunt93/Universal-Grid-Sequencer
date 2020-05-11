//
//  OGControllerSequencerAutoScale.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 11/05/2020.
//
//

#include "OGControllerSequencerAutoScale.hpp"
#include "Scales.h"


OGControllerSequencerAutoScale::OGControllerSequencerAutoScale (XY size, XY position) : OGControllerSequencerRoot(size, position, OGController::eSequencerSimple, {size.y, size.x, 8})
{
    setup(size.y);
    
    setColour ({255, 0, 0}, 0);
    setColour ({0, 255, 0}, 1);
}
void OGControllerSequencerAutoScale::messageRecieved (OGDevice::OGInMsg msg)
{
    if (msg.velocity) {
        toggleStep(getVoiceStepRef(currentSequence, msg.pos.x), msg.pos.y);
        
        const auto col = getVoiceStepRef(currentSequence, msg.pos.x).notes[msg.pos.y].velocity ? getColour(1) : LFXColor(0, 0, 0);
        lfxBuffer.writeToPositionXY(col, msg.pos.x, msg.pos.y);
        
    }
}
XY OGControllerSequencerAutoScale::getMinimumSize ()
{
    return {1,1};
}
XY OGControllerSequencerAutoScale::getMaximumSize ()
{
    return {64,64};
}
void OGControllerSequencerAutoScale::refresh ()
{
    bufferHelper.drawSquare(0, 0, size.x, size.y, {});
}
const int OGControllerSequencerAutoScale::getColoursRequired ()
{
    return 2;
}
void OGControllerSequencerAutoScale::clockPulse (int _1_4, int _1_8, int _1_16, int _1_32)
{
    //    std::cout << _1_4 << " : " << _1_8 << " : " << _1_16 << " : " << _1_32 << "\n";
    if ((_1_32 % 2) == 0) {
        const int oldStep = currentStep;
        
        increment();
        
    
        const int noteStart = (externalControlValues[OGController::eExternalControlIndexes::eOctave] * 12);
        const uint8 scaleIndex = externalControlValues[OGController::eExternalControlIndexes::eScale];
    
        const uint8 * localScalePtr = nullptr;
        uint8 len;
        pointToScale(scaleIndex, &localScalePtr, &len);
        jassert(localScalePtr != nullptr);
        
        bool isSent = false;
        for (int y = 0; y < maxVoices; y++) {
            //            uint8 index = ((maxVoices-1) - y);
            const int velocity = getVoiceStepRef().notes[y].velocity;
            if (velocity) {
                //                int noteToSend = ((maxVoices-1)-y) + rootNote;
                y = maxVoices-1 - y;
                const int oct = y / len; //how many octaves of scale are their?
                const int index = (y % len); //what position in the scale are we?
                const int scaleNote = localScalePtr[index] + oct * 12; //
                const int noteToSend = scaleNote + noteStart;
                
                sendMidi(MidiMessage::noteOn((uint8)1, noteToSend, (uint8) 100), 0);
                sendMidi(MidiMessage::noteOff((uint8)1, noteToSend, (uint8) 0), 300);
                isSent = true;
                y = maxVoices-1 - y;
                
            }
        }
        if (isSent) {
            
        }
        transferSequenceToLFX();
        bufferHelper.drawSquare(currentStep, 0, 1, size.y, getColour(0));
    }
    
    
}
void OGControllerSequencerAutoScale::transferSequenceToLFX ()
{
    for (int x = 0; x < maxSteps; x++) {
        for (int y = 0; y < maxVoices; y++) {
            if (getVoiceStepRef(currentSequence, x).notes[y].velocity) {
                lfxBuffer.writeToPositionXY(getColour(1), x, y);
            }
            else {
                lfxBuffer.writeToPositionXY({}, x, y);
            }
        }
        
    }
}
