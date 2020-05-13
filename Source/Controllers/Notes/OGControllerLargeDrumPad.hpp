//
//  OGControllerLargeDrumPad.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 04/05/2020.
//
//

#ifndef OGControllerLargeDrumPad_hpp
#define OGControllerLargeDrumPad_hpp

#include <stdio.h>
#include "OGController.hpp"
#include <array>

class OGControllerLargeDrumPad : public OGController {
public:
    OGControllerLargeDrumPad (XY size, XY position);
    ~OGControllerLargeDrumPad ();
    
    void messageReceived (OGDevice::OGInMsg msg);
    XY getMinimumSize ();
    XY getMaximumSize ();
    void refresh ();
    const int getColoursRequired ();

    
    // ------------------------------------------------------------------------------------------------
    // you can use the function
    std::array<uint8, 16> &getNoteValues ();
private:
    
    std::array<uint8, 16> noteValues = {57,49,51,53,48,47,45,43,36,40,37,39,36,40,42,46};;
    
};


#endif /* OGControllerLargeDrumPad_hpp */
