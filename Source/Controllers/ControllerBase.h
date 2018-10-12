//
//  ControllerBase.h
//  OpenGrid
//
//  Created by Samuel Hunt on 11/10/2018.
//
//

#ifndef __OpenGrid__ControllerBase__
#define __OpenGrid__ControllerBase__

#include "../JuceLibraryCode/JuceHeader.h"
/*
 The base controller is a pure virtual class:
 
 It recives inputs.
 
 It also holds a buffer which can be written to.
 
 This is later picked up by the GUI object
 */

struct XY {
    int x, y;
};

class ControllerBase {
public:
    
    enum eType {
        eNone,
        eSwitch,
        eButton,
        eSequencer,
        eExternalControl,
        eInternalControl,
        eTransport,
        eNoteGrid,
    };
    enum eControlType {
        eControlNone = 0,
        eControlSwitchPattern,
        eControlSyncPoints,
    };
    
    
    ControllerBase ();
    virtual ~ControllerBase ();
    
    //eventuall this will get replaced by a clock object..
    virtual void clockInput (const int step, const int clock) {}
    
    virtual void padInput (const int x, const int y) {}
    virtual void externalControlInput (int type, int control) {}
    
    virtual void controlInput (const int index, const int velocity, const eControlType type) {}
    
    
private:
    
};

#endif /* defined(__OpenGrid__ControllerBase__) */
