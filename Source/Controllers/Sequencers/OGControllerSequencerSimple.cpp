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
    setColour ({255, 0, 0}, 0);
}
void OGControllerSequencerSimple::messageRecieved (OGDevice::OGInMsg msg)
{
    toggleStep(getVoiceStepRef(currentSequence, msg.pos.x), msg.pos.y);
#warning FIX HERE
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
    std::cout << _1_4 << " : " << _1_8 << " : " << _1_16 << " : " << _1_32 << "\n";
  //  if ((_1_32 % 2) == 0) {
        const int oldStep = currentStep;
        bufferHelper.drawSquare(0, 0, size.x, size.y, {});
        increment();
        bufferHelper.drawSquare(currentStep, 0, 1, size.y, getColour(0));
        
        const int rootNote = 36;
        for (int y = 15; y >= 0; y--) {
            uint8 index = (15-y);
            const int velocity = getVoiceStepRef().notes[index].velocity;
            if (velocity) {
                sendMidi(MidiMessage::noteOn((uint8)1, rootNote + index, (uint8) 100));
                sendMidi(MidiMessage::noteOn((uint8)1, rootNote + index, (uint8) 0));


            }
        }
        
   // }
    
    
}
