//
//  OGSession.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef OGSession_hpp
#define OGSession_hpp

#include <stdio.h>
#include "OGDeviceManager.hpp"

// this class contains the mappings between the device amanger and subsequent controllers.

// you can have many sessions, controller by a session manager.

// we alos want a viewport type controller. that essentially shows the view of another session..


class OGController;

class OGSession {
public:
    
    struct Map {
        Map ()
        {
            controller = nullptr;
            index = -1;
            pos = {0,0};
        }
        OGController * controller; //for each XY press what is it mapped too?
        XY pos;
        int index;
    };
    
    OGSession (OGDeviceManager & devManager);
    ~OGSession ();
    void messageRecieved (OGDevice::OGInMsg msg);
    
    
    void buildMap ();
    const int getTotalControllers ();
    OGController * controllerForIndex (const int index);
    
    
private:
    OGDeviceManager & devManager;
    std::vector<Map> controlerMap;
    std::vector<OGController *> controllers;
};

#endif /* OGSession_hpp */
