//
//  OGControllerSequencerAutoScale.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 11/05/2020.
//
//

#ifndef OGControllerSequencerAutoScale_hpp
#define OGControllerSequencerAutoScale_hpp

#include "OGControllerSequencerRoot.hpp"

class OGControllerSequencerAutoScale : public OGControllerSequencerRoot {
public:
    
    OGControllerSequencerAutoScale (XY size, XY position);
    void messageReceived (OGDevice::OGInMsg msg) override;
    XY getMinimumSize () override;
    XY getMaximumSize () override;
    void refresh () override;
    const int getColoursRequired () override;
    
    void clockPulse (int _1_4, int _1_8, int _1_16, int _1_32) override;
    
    
    
    
private:
    
    void transferSequenceToLFX ();
};

#endif /* OGControllerSequencerAutoScale_hpp */
