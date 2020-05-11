//
//  OGControllerSequencerRoot.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 08/05/2020.
//
//

#include "OGControllerSequencerRoot.hpp"



OGControllerSequencerRoot::OGControllerSequencerRoot (XY size, XY position, eControllerList type, SequenceLegnths lens) : OGController(size, position, type), maxVoices(lens.numVoices), maxSteps(lens.numSteps), maxSequences(lens.numSequences)
{
    sequences.resize(lens.numSequences);
    const NoteStep ns = {0,0,0};
    
    Sequence copySeq;
    copySeq.steps.resize(lens.numSteps);
    
    //we basicly fill one sequence with nothing
    for (int i = 0; i < lens.numSteps; i++) {
        copySeq.steps[i].notes.resize(lens.numVoices);
        for (int v = 0; v < lens.numVoices; v++) {
            copySeq.steps[i].notes[v] = ns;
        }
    }
    
    for (int i = 0; i < lens.numSequences; i++) {
        sequences[i] = copySeq;
    }
    blankResuse = copySeq;

    currentSequence = 0;
    stepStart = 0;
    stepEnd = maxSteps;
    currentStep = stepEnd-1;
}




void OGControllerSequencerRoot::restartSequence ()
{
    currentStep = stepEnd-1;
}
void OGControllerSequencerRoot::increment ()
{
    currentStep++;
    if (currentStep >= stepEnd) {
        currentStep = stepStart;
    }
}
void OGControllerSequencerRoot::setStartEnd (const int start, const int end)
{
    stepStart = start;
    stepEnd = end;
}
const int OGControllerSequencerRoot::getStart ()
{
    return stepStart;
}
const int OGControllerSequencerRoot::getEnd ()
{
    return stepEnd;
}


void OGControllerSequencerRoot::copySequence (const int sequenceToCopyIndex, const int destinationIndex)
{
    jassert(sequenceToCopyIndex <sequences.size());
    jassert(destinationIndex <sequences.size());
    if (sequenceToCopyIndex == destinationIndex) {
        return;
    }
    sequences[destinationIndex] = sequences[destinationIndex];

}
void OGControllerSequencerRoot::toggleNoteStep (const int sequence, const int step, const int voice)
{
    sequences[sequence].steps[step].notes[voice].velocity = ((!sequences[sequence].steps[step].notes[voice].velocity) * 127); //wow! too many refrences :/
}
void OGControllerSequencerRoot::toggleStep (VoiceStep& step, const int voice)
{
    step.notes[voice].velocity = ((!step.notes[voice].velocity) * 127);

}

OGControllerSequencerRoot::VoiceStep& OGControllerSequencerRoot::getVoiceStepRef (const int sequence, const int step)
{
    return sequences[sequence].steps[step];

}
OGControllerSequencerRoot::VoiceStep& OGControllerSequencerRoot::getVoiceStepRef ()
{
    return sequences[currentSequence].steps[currentStep];

}
