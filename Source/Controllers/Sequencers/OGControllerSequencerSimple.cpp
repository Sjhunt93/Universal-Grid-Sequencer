//
//  OGControllerSequencerSimple.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 08/05/2020.
//
//

#include "OGControllerSequencerSimple.hpp"


OGControllerSequencerSimple::OGControllerSequencerSimple (XY size, XY position) : OGControllerSequencerRoot(size, position, OGController::eSequencerSimple, {size.y, size.x, 8})
{
    setup(size.y);

    setColour ({255, 0, 0}, 0);
       setColour ({0, 255, 0}, 1);
}
void OGControllerSequencerSimple::messageRecieved (OGDevice::OGInMsg msg)
{
    if (msg.velocity) {
        toggleStep(getVoiceStepRef(currentSequence, msg.pos.x), msg.pos.y);
        
        const auto col = getVoiceStepRef(currentSequence, msg.pos.x).notes[msg.pos.y].velocity ? getColour(1) : LFXColor(0, 0, 0);
        lfxBuffer.writeToPositionXY(col, msg.pos.x, msg.pos.y);
        
    }
}
XY OGControllerSequencerSimple::getMinimumSize ()
{
    return {1,1};
}
XY OGControllerSequencerSimple::getMaximumSize ()
{
    return {64,64};
}
void OGControllerSequencerSimple::refresh ()
{
    bufferHelper.drawSquare(0, 0, size.x, size.y, {});
}
const int OGControllerSequencerSimple::getColoursRequired ()
{
    return 2;
}
void OGControllerSequencerSimple::clockPulse (int _1_4, int _1_8, int _1_16, int _1_32)
{
//    std::cout << _1_4 << " : " << _1_8 << " : " << _1_16 << " : " << _1_32 << "\n";
   if ((_1_32 % 2) == 0) {
        const int oldStep = currentStep;

        increment();

        
        const int rootNote = 60;
        bool isSent = false;
        for (int y = 0; y < maxVoices; y++) {
//            uint8 index = ((maxVoices-1) - y);
            const int velocity = getVoiceStepRef().notes[y].velocity;
            if (velocity) {
//                int noteToSend = ((maxVoices-1)-y) + rootNote;
                const int noteToSend = noteMap.values[(maxVoices-1)-y];
                sendMidi(MidiMessage::noteOn((uint8)1, noteToSend, (uint8) 100), 0);
                sendMidi(MidiMessage::noteOff((uint8)1, noteToSend, (uint8) 0), 300);
                isSent = true;

            }
        }
    if (isSent) {
        
    }
    transferSequenceToLFX();
    bufferHelper.drawSquare(currentStep, 0, 1, size.y, getColour(0));
  }
    
    
}
void OGControllerSequencerSimple::transferSequenceToLFX ()
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
