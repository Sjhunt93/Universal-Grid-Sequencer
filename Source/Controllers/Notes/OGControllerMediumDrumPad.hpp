//
//  OGControllerMediumDrumPad.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 07/05/2020.
//
//

#ifndef OGControllerMediumDrumPad_hpp
#define OGControllerMediumDrumPad_hpp

#include <stdio.h>
#include "OGController.hpp"
#include "LFXFacade.hpp"
#include <array>

class OGControllerMediumDrumPad : public OGController {
public:
    OGControllerMediumDrumPad (XY size, XY position);
    ~OGControllerMediumDrumPad ();
    
    void messageReceived (OGDevice::OGInMsg msg);
    XY getMinimumSize ();
    XY getMaximumSize ();
    void refresh ();
    const int getColoursRequired ();
    
    
    // ------------------------------------------------------------------------------------------------
    // you can use the function
    std::array<uint8, 16> &getNoteValues ();
    std::array<LFXColor, 16> &getColourValues (); //as soon as this is called the internal
private:

    std::array<uint8, 16> noteValues = {57,49,51,53,48,47,45,43,36,40,37,39,36,40,42,46};;
    std::array<LFXColor, 16> customColours;
    bool useCustomColours = false;
    
};

#endif /* OGControllerMediumDrumPad_hpp */
