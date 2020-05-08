//
//  OGDeviceManager.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef OGDeviceManager_hpp
#define OGDeviceManager_hpp

#include "OGDevice.hpp"
#include "InputBuffer.hpp"

/*
 
 // if the vector is a 2x2 grid
 |------|------|
 |  1   | 2    |
 |      |      |
 |------|------|
 | 3    | 4    |
 |      |      |
 |------|------|

 so in the example above we have 4 grid controllers, each with an 9x9 grid
 
 we therefore have a padGridSize of 18x18
 
 */

class OGSession;
class OGDeviceManager {
public:
    
    enum eDeviceType {
        eLaunchpadRG,
    };
    
    struct Map {
        OGDevice * originalDevice;
        XY pos;
        int index;
    };
    
    OGDeviceManager (XY size);
    ~OGDeviceManager ();
    
    void createNewDevice (eDeviceType type, XY position, String midIn, String midiOut);
    //ok so these two are confusing.
    
    // the first is for getting acssess to the devices with the devices vector
    OGDevice * deviceAtPosInVector (XY pos);
    
    // this returns the device for the pad position this uses the devicemap
    // this is mostly used to seend LEDfeedback to the relevant device.
    OGDevice * deviceForPadPosition (XY pos);
    
    void deleteDevices (XY position);
    const XY gridSize; //can be public as const
    const XY getPadGridSize ();
    
    void messageRecieved (OGDevice * device, OGDevice::OGInMsg msg);
    
    void createMap ();
    
    /*
     The following 2 methods are both called from the masterClock Thread.
     This ensures that there is both syncronicty between controllers (time based)
     and concurency and no data races, or read write errors.
     
     
     MIDIThread -> messageRecieved() -> InputBuffer...
     
     MasterClockThread -> dispatchBufferToControllers() -> reads from InputBuffer -> messageBufferLocal;
     MasterClockThread -> messageBufferLocal -> to session. 
     
     once in the session callbacks these send messages directly to MIDI out (JUCE handles the trasnfer back to the MIDIThread
     
     MasterClockThread -> collectLFXBuffers ()
     
     again this just sends LED feedback.
     
     */
    void dispatchBufferToControllers (OGSession * sessionToSendToo); //this is called from the main clock thread.
    void collectLFXBuffers (OGSession * session); //this goes through and transfers all session buffers to the master device buffer.
    
    void testSendFeedback (XY pos);
    
    void sendMidiMessageMaster (MidiMessage m);
private:
    std::vector<OGDevice *> devices; //stores devices
    std::vector<Map> deviceMap; //stores device position relative to a pad press.
    XY padGridSize;
    
    
    //these two deal with Message input
    InputBuffer messageBuffer;
    std::array<OGDevice::OGInMsg, 50> messageBufferLocal;
    
//    LFXBuffer   deviceBufferCollect; //this holds all the data colleced from the session buffers
    //std::unique_ptr<LFXBuffer> deviceBufferSend; //this is the buffer that gets sent, i.e we transfer from collect to send, and only then send the updates.
    LFXBuffer * deviceBufferSend; //this is the buffer that gets sent, i.e we transfer from collect to send, and only then send the
    std::unique_ptr<MidiOutput> deviceOutput;
    
};

#endif /* OGDeviceManager_hpp */
