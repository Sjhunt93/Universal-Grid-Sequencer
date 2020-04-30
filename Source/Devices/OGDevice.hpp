//
//  OGDevice.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef OGDevice_hpp
#define OGDevice_hpp

#include "../JuceLibraryCode/JuceHeader.h"

struct XY {
    int x;
    int y;
    
    XY operator+(const XY xy)
    {
        x += xy.x;
        y += xy.y;
        return *this;
    }
    XY operator-(const XY xy)
    {
        x -= xy.x;
        y -= xy.y;
        return *this;
    }
    
};


class OGDevice : public MidiInputCallback {
public:
    
    enum eOrientation {
        eNormal,
        eRotatedLeft,
        eRotatedRight,
        eRotated180,
    };
    
    enum eInputType {
        eMomentryPad, //non velocity sensitive
        eVelocityPad,
        ePressurePad,
        eContinousPad,
    };
    
    struct OGInMsg { //input message
        XY pos;
        eInputType type;
        int velocity;
    };
    
    /*
     This used by the GUI to draw a representation of the pysical device, i.e. the GUI will send repeated messages to pysicalElementForXY
     */
    enum ePysicalRepresentation {
        eNone, //some grids for example launchpad do not actually have anything at position 0,0
        eSquareButton,
        eRoundButton,
        eRotary,
    };
    
    enum eColourType {
        eMono, //single on/off
        eRG, // launchpad
        eRGB, // full colour
    };
    
    struct OGColour {
        float red;
        float blue;
        float green;
    };
    
    
    OGDevice (String MIDINameIn, String MIDINameOut);
    virtual ~OGDevice ();
    
    void setOrientation (eOrientation orientation); //by default all devices will be in eNormal
    
    // The device will need to implement this
    virtual void setFeedback (OGColour colour, XY position) = 0;

    //you can use this to return a position from one orientation to another this assumes the grid is rectangular
    XY getNeturalXY (XY position);
    XY getOrientatedXY (XY position); //does the oppisite

    

    
    const XY getTotalGridSize (); //this is the arbitary size of the grid.
    const String getDeviceName ();
    virtual const OGDevice::ePysicalRepresentation getPysicalElementForXY (XY pos) = 0;
    virtual const eColourType getColourType () = 0;
    const bool hasConnectedOk ();
    virtual void resetDevice () = 0;
    
    std::function<void(OGInMsg, OGDevice *)> callbackOGInMsg; //called when a new message is recieved.
    
    XY offset; //relative offset used in the device manager
    
protected:
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) {}
    std::unique_ptr<MidiInput> inDevice;
    std::unique_ptr<MidiOutput> outDevice;
    
    String          deviceName; //set by the interface, this might be for example Launchpad top left.
    XY              gridSize;
    eOrientation    currentOrientation;
    
};

#endif /* OGDevice_hpp */
