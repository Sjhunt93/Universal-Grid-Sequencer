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
#include "LFXFacade.hpp"

class OGController {
public:
    
    /*
     To create a new controller you will need to overide the following functions.
     
        OGController (XY size, XY position);
        void messageRecieved (OGDevice::OGInMsg msg);
        XY getMinimumSize ();
        XY getMaximumSize ();
        void refresh ();
        const int getColoursRequired ();

     
        these are optional
        void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32, int _1_64);
        void clockPulse (int ticks);
        const int getNumberOfExternalControls ();
        ExternalControlMessage getDescriptionForExternalControl ();
     

     */
    
    enum eControllerList {
        eTest,
        eDrumLargePad,
    };
    
    
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
    struct ExternalControlMessage {
        String name;
        
    };
    
    struct GlobalControls {
        
        //whole steps i.e. a range of 0 - 8, will play all steps starting with the first up to the end.
        int seqStart;
        int seqEnd;
        int clockStepDivision;
        
    };
    
    enum eExternalControlIndexes {
        eSeqStart,
        eSeqEnd,
        eClockStepDivision,
        eScale,
        eChannel,
        eExternalCustomStart,
    };
    
    
    
    OGController (XY size, XY position, const eControllerList type);
    virtual ~OGController ();
    void setup (); //this is used to resize through a virtual function so must be called after construction..
    
    
    virtual void refresh () = 0;
    
    virtual void messageRecieved (OGDevice::OGInMsg msg) = 0;
    virtual void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32) {}
    virtual void clockPulseTicks (int ticks) {}

    
    //position stuff
    virtual XY getMinimumSize () = 0;
    virtual XY getMaximumSize () = 0;
    const XY size;
    const XY position;

    // Colour functions
    virtual const int getColoursRequired () = 0; //how many colours does this controller require
    void setColour (LFXColor col, const int index);
    LFXColor getColour (const int index);
    
    
    // external controls
    virtual const int getNumberOfExternalControls () {return eExternalCustomStart;}
    virtual ExternalControlMessage getDescriptionForExternalControl () {return {};}
    void setExternalControl (const int index, int value);
    
    
    
    LFXBuffer& getLFXBuffer ();
    
    void sendMidi (MidiMessage m);
    std::function<void(MidiMessage)> sendMidiOutput; //this will be called from the clock thread.
    
    const eControllerList type;
    
    
    static OGController * allocateForType (eControllerList type); //the caller of this function takes ownership of the returned class.
protected:

    LFXBuffer lfxBuffer;
    LFXFacade bufferHelper;
    std::vector<LFXColor> colorList;
    std::vector<int>      externalControlValues;
};
#endif /* OGController_hpp */
