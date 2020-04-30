//
//  OGController.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 30/04/2020.
//
//

#ifndef OGController_hpp
#define OGController_hpp

#include <stdio.h>
#include "OGDevice.hpp"
#include "LFXBuffer.h"

class OGController {
public:
    
    //each controller has a LEDfeedback buffer
    // this can be setup to use a number of layers.
    
    enum eModeType {
        eModeTypeMomentry = 0, //note/drums etc
        eModeTypeSequencer,
        eModeTypeUtil, //helper class, for mode selection and such
        eModeTypeContainer, //a container technically holds multiple modes.
        eModeTypeViewport,
        eModeTypeOther,
    };
    enum eModeOperation {
        eOffline = 0, //will not recive clock or input messages
        eLive, //is the only mode reciving messages
        eExternal, //has an external register attached
    };
    
    OGController (XY size, XY position);
    virtual ~OGController ();

    virtual void messageRecieved (OGDevice::OGInMsg msg) = 0;
    virtual void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32, int _1_64) {}
    virtual void clockPulse (int ticks) {}


    
    const XY size;
    const XY position;
    
    int numberOfBuffers;
    int selectedBufferl;
    
    LFXBuffer& getLFXBuffer ();
private:

    LFXBuffer lfxBuffer;
};
#endif /* OGController_hpp */
