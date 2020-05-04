//
//  LFXFacade.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 04/05/2020.
//
//

#include "LFXFacade.hpp"


LFXFacade::LFXFacade (LFXBuffer & buf) : buffer(buf)
{
    
}



void LFXFacade::drawSquare (const int xPos, const int yPos, const int width, const int height, LFXColor color)
{
    
    for (int x = xPos; x < xPos + width; x++) {
        for (int y = yPos; y < yPos + height; y++) {
            if (buffer.check(x, y)) {
                buffer.writeToPositionXY(color, x, y);
            }
        }
    }
    
    
    
}
