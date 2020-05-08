//
//  OGControllerSequencerRoot.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 08/05/2020.
//
//

#ifndef OGControllerSequencerRoot_hpp
#define OGControllerSequencerRoot_hpp



#include "OGController.hpp"

class OGControllerSequencerRoot : public OGController  {
public:
    
    struct NoteStep {
        uint8  velocity;
        uint8  noteLen;
        short  flags; //other 1 bit flags, /*** will define later!
        
    };
    
    struct VoiceStep {
        std::vector<NoteStep> notes; // a voice step contains
    };
    
    struct Sequence {
        std::vector<VoiceStep> steps;
    };
    
    struct SequenceLegnths {
        int numVoices;
        int numSteps;
        int numSequences;
    };

    
     
    OGControllerSequencerRoot (XY size, XY position, eControllerList type, SequenceLegnths lens);
    virtual ~OGControllerSequencerRoot() {}
    
    void restartSequence ();
    void setStartEnd (const int start, const int end);
    
    const int getStart ();
    const int getEnd ();
    
    void increment ();
    
    void copySequence (const int sequenceToCopyIndex, const int destinationIndex);
    void toggleNoteStep (const int sequence, const int step, const int voice);
    void toggleStep (VoiceStep& step, const int voice);
    
    VoiceStep& getVoiceStepRef (const int sequence, const int step);
    VoiceStep& getVoiceStepRef ();
protected:
    int currentStep;
    int stepStart;
    int stepEnd;
    int currentSequence;
    

    std::vector<Sequence> sequences;
    const int maxVoices, maxSteps, maxSequences;
private:
    Sequence blankResuse;


};
#endif /* OGControllerSequencerRoot_hpp */
