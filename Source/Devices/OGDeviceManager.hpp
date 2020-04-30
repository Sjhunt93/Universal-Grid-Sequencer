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
    
    void dispatchBufferToControllers (OGSession * sessionToSendToo); //this is called from the main clock thread.
    
    
    void testSendFeedback (XY pos);
private:
    std::vector<OGDevice *> devices; //stores devices
    std::vector<Map> deviceMap; //stores device position relative to a pad press.
    XY padGridSize;
    InputBuffer messageBuffer;
    std::array<OGDevice::OGInMsg, 50> messageBufferLocal;
    
};

#endif /* OGDeviceManager_hpp */
