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
        void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32);

        void clockPulse (int ticks);
        const int getNumberOfExternalControls ();
        ExternalControlMessage getDescriptionForExternalControl ();
     

     */
    
    enum eControllerList {
        eTest,
        eDrumLargePad,
        eSequencer,
        eSequencerSimple,
        eNoteScaleRepeater,
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
    struct ExternalControlDescription {
        String name;
        float minValue, maxValue, divisionValue;
        //division value is simply
    };
    
    struct GlobalControls {
        
        //whole steps i.e. a range of 0 - 8, will play all steps starting with the first up to the end.
        int seqStart;
        int seqEnd;
        int clockStepDivision;
        
    };
    
    enum eExternalControlIndexes {
        eSeqStart, //what step should the sequence start at
        eSeqEnd, //what step should the sequence end at
        eClockStepDivision, //how fast should the clock be devided
        eScale, //what scale should the controller use
        eChannel, //what channel should the controller send on
        eStartNote,
        eOveralp,
        eOctave, //what octave should the sequence start at
        eTranpose,
        eRelease,
        eExternalCustomStart,
    };
    
    struct ControlMessage {
        XY pos;
        int value;
        String cName;
    };
    
    /*
     A note map is used by a controller for determining what each row/step etc is mapped to what note.
     For example in a step sequencer with 4 rows, you have a 4 element note map that might look like:
     
        36, //kick
        38, //snare
        42, //hat closed
        46, //hat open
     
     
     Not every controller needs to use a NoteMap, as some are computed algorithmically
     
     this structure is returned below
     */
    struct NoteMap {
        std::vector<int> values;
        bool transposable;
    };
    
    OGController (XY size, XY position, const eControllerList type);
    virtual ~OGController ();
    void setup (const int noteMapSize = 1); //this is used to resize through a virtual function so must be called after construction..
    
    
    virtual void refresh () = 0;
    
    virtual void messageRecieved (OGDevice::OGInMsg msg) = 0;
    virtual void controlMessageRecieved (ControlMessage msg) {}
    virtual void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32) {}
    virtual void clockPulseTicks (int ticks) {}

    // ----------------------------------------------------------------------------------------------------
    //position stuff
    virtual XY getMinimumSize () = 0;
    virtual XY getMaximumSize () = 0;
    const XY size;
    const XY position;

    // ----------------------------------------------------------------------------------------------------
    // Colour functions
    virtual const int getColoursRequired () = 0; //how many colours does this controller require
    void setColour (LFXColor col, const int index);
    LFXColor getColour (const int index);
    
    // ----------------------------------------------------------------------------------------------------
    // external controls
#warning THIS NEEDS sorting...
    virtual const int getNumberOfExternalControls () {return eExternalCustomStart;}
    virtual ExternalControlMessage getDescriptionForExternalControl () {return {};}
    void setExternalControl (const int index, int value);
    
    
    // ----------------------------------------------------------------------------------------------------
    LFXBuffer& getLFXBuffer ();
    NoteMap & getNoteMap ();
    
    
    // ----------------------------------------------------------------------------------------------------
    // MIDI
    
    void sendMidi (MidiMessage m, int delay); //call this rather than the std::function below, as this function will check that sendMidiOutput is not nullptr!
    std::function<void(MidiMessage,int)> sendMidiOutput; //this will be called from the clock thread.
    

    void sendControl (ControlMessage control);
    std::function<void(ControlMessage)> sendControlMessage; //some controllers are able to send control message, i.e. clock start. these are all managed in the session manager..
    
    
    const eControllerList type;
    
    
    static OGController * allocateForType (eControllerList type); //the caller of this function takes ownership of the returned class.
protected:

    LFXBuffer lfxBuffer;
    LFXFacade bufferHelper;
    std::vector<LFXColor> colorList;
    std::vector<int>      externalControlValues;
    
    void initNoteMap (const int size);
    NoteMap               noteMap;
};
#endif /* OGController_hpp */
