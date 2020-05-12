//
//  OGSessionTemplates.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 11/05/2020.
//
//

#ifndef OGSessionTemplates_hpp
#define OGSessionTemplates_hpp

#include "../JuceLibraryCode/JuceHeader.h"

#include "OGDeviceLaunchpad.hpp"
#include "OGDeviceManager.hpp"
#include "MasterClock.hpp"
#include "OGSession.hpp"
#include "OGControllerLargeDrumPad.hpp"
#include "OGControllerMediumDrumPad.hpp"
#include "OGControllerSequencerSimple.hpp"
#include "OGControllerSequencerAutoScale.hpp"
#include "OGControllerNoteScaleRepeater.hpp"

class OGSessionTemplates {
public:
    class Base {
        
    public:
        Base () : deviceManager({2,2})
        {
            //---------------------------------------------------------------------------------------------------------------------------------------
            //set up the device manager
            deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {0,0}, "Launchpad Mini", "Launchpad Mini");
            deviceManager.deviceAtPosInVector({0,0})->setOrientation(OGDevice::eOrientation::eRotatedLeft);
            
            
            deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {1,0}, "Launchpad Mini 2", "Launchpad Mini 2");
            deviceManager.deviceAtPosInVector({1,0})->offset = {9,0};
            
            deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {0,1}, "Launchpad Mini 3", "Launchpad Mini 3");
            deviceManager.deviceAtPosInVector({0,1})->setOrientation(OGDevice::eOrientation::eRotated180);
            deviceManager.deviceAtPosInVector({0,1})->offset = {0,9};
            
            deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {1,1}, "Launchpad Mini 4", "Launchpad Mini 4");
            deviceManager.deviceAtPosInVector({1,1})->setOrientation(OGDevice::eOrientation::eRotatedRight);
            deviceManager.deviceAtPosInVector({1,1})->offset = {9,9};
            
            deviceManager.createMap();
            
            session = std::make_unique<OGSession>(deviceManager, mClock);
            
            mClock.frameBufferCallback = [this]()
            {
                deviceManager.collectLFXBuffers(session.get());
            };
            mClock._1msCallback = [this]()
            {
                deviceManager.dispatchBufferToControllers(session.get());
            };
            
            mClock.sendMidiMessage = [this](MidiMessage m)
            {
                deviceManager.sendMidiMessageMaster(m);
            };
            
            
        }
        
        
        
        MasterClock     mClock;
        OGDeviceManager deviceManager;
        
        std::unique_ptr<OGSession>    session;
    };
    
    class Sequencer2 : public Base {
    public:
        Sequencer2 () {
        {
            OGController * cc = new OGControllerSequencerSimple( {16, 4}, {1,1});
            cc->getNoteMap().values[0] = 36;
            cc->getNoteMap().values[1] = 38;
            cc->getNoteMap().values[2] = 42;
            cc->getNoteMap().values[3] = 46;
            session->addNewController(cc );
        }
        {
            OGController * cc = new OGControllerSequencerSimple( {16, 4}, {1,6});
            cc->getNoteMap().values[0] = 36;
            cc->getNoteMap().values[1] = 38;
            cc->getNoteMap().values[2] = 42;
            cc->getNoteMap().values[3] = 46;
            session->addNewController(cc );
        }
        
        mClock.addNewClock(120);
        mClock.addNewClock(131);
        mClock.getClock(0)->addController(session->controllerForIndex(0));
        mClock.getClock(1)->addController(session->controllerForIndex(1));
        //    mClock.getClock(0)->addController(session->controllerForIndex(2));
        //    mClock.getClock(0)->addController(session->controllerForIndex(1));
        
        mClock.start();
            
        }
        
    };
    class Sequencer8 : public Base {
    public:
        Sequencer8 () {
            {
                
//                const int major[] = {60, 62, 64,65,67,69,71,72};
                const int major[] = {60, 62, 63, 65,67,68,70,72};
                for (int i = 0; i < 8; i++) {
                    OGController * cc = new OGControllerSequencerSimple( {15, 1}, {1,i+1});
                    cc->getNoteMap().values[0] = major[i];
                    session->addNewController(cc);
                    mClock.addNewClock(120+i);
                    mClock.getClock(i)->addController(session->controllerForIndex(i));
                }
                
                mClock.start();
    
            }
            
            
        }

    };
    
    class Sequencer2_8 : public Base {
    public:
        Sequencer2_8 () {
            {
                
                //                const int major[] = {60, 62, 64,65,67,69,71,72};
                const int notes[] = {64, 66, 71, 73, 74};
                
                
                
                { // controller top
                    OGController * cc = new OGControllerSequencerSimple( {12, 5}, {1,1});
                    for (int i = 0; i < 5; i++) {
                        cc->getNoteMap().values[i] = notes[i] - 12;
                    }
                    session->addNewController(cc);
                    mClock.addNewClock(120);
                    mClock.getClock(0)->addController(session->controllerForIndex(0));
                }
                { // controller bottom
                    OGController * cc = new OGControllerSequencerSimple( {12, 5}, {1,9});
                    for (int i = 0; i < 5; i++) {
                        cc->getNoteMap().values[i] = notes[i] - 12;
                    }
                    session->addNewController(cc);

                    mClock.addNewClock(121);
                    mClock.getClock(1)->addController(session->controllerForIndex(1));
                }
                
                
                
                
                mClock.start();
                
            }
            
            
        }
        
    };
    
    class Sequencer15 : public Base {
    public:
        Sequencer15 () {
            {
                
                //                const int major[] = {60, 62, 64,65,67,69,71,72};
                const int major[] = {60, 62, 63, 65,67,68,70,72,74,76,77,79,81,83,84};
                for (int i = 0; i < 15; i++) {
                    OGController * cc = new OGControllerSequencerSimple( {15, 1}, {1,i+1});
                    cc->getNoteMap().values[0] = major[i];
                    session->addNewController(cc);
                    mClock.addNewClock(120+(i*0.5));
                    mClock.getClock(i)->addController(session->controllerForIndex(i));
                }
                
                mClock.start();
                
            }
            
            
        }
        
    };
    
    class Sequencer16Full : public Base {
    public:
        Sequencer16Full ()
        {
            OGControllerSequencerAutoScale * scale = new OGControllerSequencerAutoScale({16,16}, {1,1});
            session->addNewController(scale);
            mClock.addNewClock(120);
            mClock.getClock(0)->addController(session->controllerForIndex(0));
            mClock.start();



        }
//
    };
    
    
    class PolyRhythmTester : public Base {
    public:
        PolyRhythmTester () {
            {
                
                const int notes[] = {60, 62, 64,65,67,69,71,72};
                //const int notes[] = {64, 66, 71, 73, 74};
                
                
                
                { // controller top
                    OGController * cc = new OGControllerSequencerSimple( {13, 8}, {1,1});
                    for (int i = 0; i < 8; i++) {
                        cc->getNoteMap().values[i] = notes[i];
                    }
                    session->addNewController(cc);
                    mClock.addNewClock(120*(13.0/12.0));
                    mClock.getClock(0)->addController(session->controllerForIndex(0));
                }
                { // controller bottom
                    OGController * cc = new OGControllerSequencerSimple( {12, 8}, {1,9});
                    for (int i = 0; i < 8; i++) {
                        cc->getNoteMap().values[i] = notes[i] - 12;
                    }
                    session->addNewController(cc);
                    
                    mClock.addNewClock(120);
                    mClock.getClock(1)->addController(session->controllerForIndex(1));
                }
                
                
                
                
                mClock.start();
                
            }
            
            
        }
        
    };
    
    class NoteScaleRepeaterTester : public Base {
    public:
        NoteScaleRepeaterTester ()
        {
            OGController * cc = new OGControllerNoteScaleRepeater({16,16}, {1,1});
            session->addNewController(cc);
            
            mClock.start();

        }


        
    };

    
    

    
    
    //    session->addNewController(new OGControllerSequencerSimple( {14, 4}, {1,9}));
    

    
};

#endif /* OGSessionTemplates_hpp */
