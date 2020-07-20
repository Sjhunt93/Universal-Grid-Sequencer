//
//  OGSessionAudioMostlyTemplates.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 30/05/2020.
//
//

#ifndef OGSessionAudioMostlyTemplates_hpp
#define OGSessionAudioMostlyTemplates_hpp

#include "OGSessionTemplates.hpp"


// Polytempic examples.

//this
class AMSequencerSimpleDrumSequencer : public OGSessionTemplates::Base {
public:
    AMSequencerSimpleDrumSequencer ()
    {
        // [1] the inner set is size {16 steps, 4 voices}, the outer set is position {x: 1, y:1}
        OGController * drumControler = new OGControllerSequencerSimple( {16, 4}, {1,1});
        
        //[2] now we setup the note map, each index is the voice (row)
        drumControler->getNoteMap().values[0] = 36; //kick
        drumControler->getNoteMap().values[1] = 38; //snare
        drumControler->getNoteMap().values[2] = 42; //closed hi-hat
        drumControler->getNoteMap().values[3] = 46; //open hi-hat
        
        //[3] add our new controller to the session
        session->addNewController(drumControler);
        
        //[4] create a new clock with a tempo of 140 bpm
        mClock.addNewClock(140);
        
        //[5] we only have 1 clock and 1 controller so we assume 0 index
        mClock.getClock(0)->addController(session->controllerForIndex(0));
        
        //[6] start the master clock
        mClock.start();
        
    }
};


class AMSequencer2WayPolyrthmicContainer : public OGSessionTemplates::Base {
public:
    AMSequencer2WayPolyrthmicContainer (const int step1, const int step2, const float tempo1) { //16 / 12
        {
            
            jassert (step1 > step2);
            const int notes[] = {60, 62, 64,65,67,69,71,72};
            //const int notes[] = {64, 66, 71, 73, 74};
            
            const float tempo2 = tempo1 * ((float)step2 / (float) step1);
            
            { // controller top
                OGController * cc = new OGControllerSequencerSimple( {step1, 8}, {1,1});
                for (int i = 0; i < 8; i++) {
                    cc->getNoteMap().values[i] = notes[i];
                }
                session->addNewController(cc);
                mClock.addNewClock(tempo1);
                mClock.getClock(0)->addController(session->controllerForIndex(0));
            }
            { // controller bottom
                OGController * cc = new OGControllerSequencerSimple( {step2, 8}, {1,9});
                for (int i = 0; i < 8; i++) {
                    cc->getNoteMap().values[i] = notes[i] - 12;
                }
                session->addNewController(cc);
                
                mClock.addNewClock(tempo2);
                mClock.getClock(1)->addController(session->controllerForIndex(1));
            }
            
            
            
            
            mClock.start();
            
        }
        
        
    }
    
};

class AMSequencerPolymeter : public OGSessionTemplates::Base {
public:
    AMSequencerPolymeter () {
        {
            OGController * cc = new OGControllerSequencerSimple( {16, 4}, {1,1});
            cc->getNoteMap().values[0] = 36;
            cc->getNoteMap().values[1] = 38;
            cc->getNoteMap().values[2] = 42;
            cc->getNoteMap().values[3] = 46;
            session->addNewController(cc );
        }
        {
            OGController * cc = new OGControllerSequencerSimple( {10, 4}, {1,9});
            cc->getNoteMap().values[0] = 36;
            cc->getNoteMap().values[1] = 38;
            cc->getNoteMap().values[2] = 42;
            cc->getNoteMap().values[3] = 46;
            session->addNewController(cc );
        }
        
        mClock.addNewClock(120);
        mClock.getClock(0)->addController(session->controllerForIndex(0));
        mClock.getClock(0)->addController(session->controllerForIndex(1));
        //    mClock.getClock(0)->addController(session->controllerForIndex(2));
        //    mClock.getClock(0)->addController(session->controllerForIndex(1));
        
        mClock.start();
        
    }
    
};


class AMSequencerPolytempo : public OGSessionTemplates::Base {
public:
    AMSequencerPolytempo () {
        {
            
            
            const int scale[] = {72, 71, 69, 67, 65, 64, 62, 60};
            
            for (int i = 0; i < 8; i++) {
                OGController * cc = new OGControllerSequencerSimple( {15, 1}, {1,i+1});
                cc->getNoteMap().values[0] = scale[i];
                session->addNewController(cc);
                mClock.addNewClock(120+i);
                mClock.getClock(i)->addController(session->controllerForIndex(i));
            }
            
            mClock.start();
            
        }
        
        
    }
    
};

class AMSequencerPolytempo2 : public OGSessionTemplates::Base {
public:
    AMSequencerPolytempo2 () {
        {
            
            
            const int major[] = {60, 62, 64, 65, 67, 69, 71, 72};
            for (int i = 0; i < 16; i++) {
                OGController * cc = new OGControllerSequencerSimple( {16, 1}, {1,i+1});
                
                session->addNewController(cc);
                if (i < 8) {
                    cc->getNoteMap().values[0] = (major[i%8] - 12);
                    mClock.addNewClock(120+(i*0.5));
                }
                else {
                    cc->getNoteMap().values[0] = (major[i%8]);
                    mClock.addNewClock(120-((i-8)*0.5));
                }
                
                mClock.getClock(i)->addController(session->controllerForIndex(i));
            }
            
            mClock.start();
            
        }
        
        
    }
    
};

#endif /* OGSessionAudioMostlyTemplates_hpp */
