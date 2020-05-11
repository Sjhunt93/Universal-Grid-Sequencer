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
    
    class Sequencer8 : public Base {
        
        Sequencer8 () {
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
    

    
    
    //    session->addNewController(new OGControllerSequencerSimple( {14, 4}, {1,9}));
    

    
};

#endif /* OGSessionTemplates_hpp */