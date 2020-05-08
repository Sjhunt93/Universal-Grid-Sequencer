//
//  OGControllerSequencerSimple.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 08/05/2020.
//
//

#ifndef OGControllerSequencerSimple_hpp
#define OGControllerSequencerSimple_hpp

#include "OGControllerSequencerRoot.hpp"

class OGControllerSequencerSimple : public OGControllerSequencerRoot {
public:
    
    OGControllerSequencerSimple (XY size, XY position);
    void messageRecieved (OGDevice::OGInMsg msg) override;
    XY getMinimumSize () override;
    XY getMaximumSize () override;
    void refresh () override;
    const int getColoursRequired () override;
    
    void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32) override;
    
    
    
    
private:

    void transferSequenceToLFX ();
};

#endif /* OGControllerSequencerSimple_hpp */
