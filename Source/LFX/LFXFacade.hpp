//
//  LFXFacade.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 04/05/2020.
//
//

#ifndef LFXFacade_hpp
#define LFXFacade_hpp

#include "LFXBuffer.h"

class LFXFacade {
public:
    LFXFacade (LFXBuffer & buffer);
    
    void drawSquare (const int x, const int y, const int width, const int height, LFXColor color);

    
private:
    LFXBuffer & buffer;
};


#endif /* LFXFacade_hpp */
