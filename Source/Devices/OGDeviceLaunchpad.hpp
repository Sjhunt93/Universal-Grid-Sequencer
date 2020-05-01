//
//  OGDeviceLaunchpad.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef OGDeviceLaunchpad_hpp
#define OGDeviceLaunchpad_hpp

#include "OGDevice.hpp"

class OGDeviceLaunchpad : public OGDevice {
public:
    

    OGDeviceLaunchpad (String MIDINameIn, String MIDINameOut);
    virtual ~OGDeviceLaunchpad ();
    
    
    void setFeedback (LFXColor colour, XY position);
    const ePysicalRepresentation getPysicalElementForXY (XY pos);
    const eColourType getColourType ();
    void resetDevice ();

protected:
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message);
};
#endif /* OGDeviceLaunchpad_hpp */
