//
//  OGControllerNoteScaleRepeater.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 12/05/2020.
//
//

#ifndef OGControllerNoteScaleRepeater_hpp
#define OGControllerNoteScaleRepeater_hpp

#include <stdio.h>
#include "OGController.hpp"
#include "LFXFacade.hpp"
#include <array>

class OGControllerNoteScaleRepeater : public OGController {
public:
    

    struct NMap {
        bool isInScale;
        int note;
    };
    
    OGControllerNoteScaleRepeater (XY size, XY position);
    ~OGControllerNoteScaleRepeater ();
    
    void messageRecieved (OGDevice::OGInMsg msg);
    XY getMinimumSize ();
    XY getMaximumSize ();
    void refresh ();
    const int getColoursRequired ();
private:
    std::vector<NMap> noteMap; //index via x + y*xSize;
};
#endif /* OGControllerNoteScaleRepeater_hpp */
