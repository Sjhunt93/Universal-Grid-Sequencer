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
#include "LFXFacade.hpp"


class OGControllerLargeDrumPad : public OGController {
public:
    OGControllerLargeDrumPad (XY size, XY position);
    ~OGControllerLargeDrumPad ();
    
    void messageRecieved (OGDevice::OGInMsg msg);
    XY getMinimumSize ();
    XY getMaximumSize ();
    void refresh ();
    const int getColoursRequired ();

private:
    LFXFacade bufferHelper;
};


#endif /* OGControllerLargeDrumPad_hpp */
