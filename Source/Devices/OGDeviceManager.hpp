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
    OGDevice * deviceAtPos (XY pos);
    
    void deleteDevices (XY position);
    const XY gridSize; //can be public as const
    
    void messageRecieved (OGDevice * device, OGDevice::OGInMsg msg);
    
    void createMap ();
private:
    std::vector<OGDevice *> devices;
    std::vector<Map> deviceMap;
    XY padGridSize;
    
};

#endif /* OGDeviceManager_hpp */
