//
//  LFXBuffer.h
//  Crayon
//
//  Created by Samuel Hunt on 23/07/2015.
//
//

#ifndef __Crayon__LFXBuffer__
#define __Crayon__LFXBuffer__

#include <iostream>
#include "LFXColor.h"
#include <fstream>


class LFXBuffer {
public:
    LFXBuffer (const int rows, const int columns);
    LFXBuffer (const LFXBuffer& other); //we need to make sure the copy is correct...
    ~LFXBuffer ();
    
    void setBufferBlend (const bool blend);

    
    LFXColor& colorForIndex (const int index);
    LFXColor& colorForPostion (const int row, const int column);
    void writeToIndex (LFXColor input, const int index);
    void writeToPosition (LFXColor input, const int row, const int column);
    void writeToPositionXY (LFXColor input, const int x, const int y);
    
    //essentially this checks to see if the colour at the position is already the same.
    //If this returns true we don't need to send any feedback
    bool writeOptimised (LFXColor input, const int x, const int y);
    
    //simple index checker.
    bool check (const int x, const int y);
    
    void blendWithBuffer (LFXBuffer other); //only supported with RGB
    void blendWithColor (LFXColor color);
    void operator=(const LFXBuffer& other);
    
    void shiftGridLR (int value); //positive for right, negative for left, THIS IS DESTRUCTIVE
    void shiftGridUD (int value); //positive for down, negative for up.
    
    void replaceColour (LFXColor old, LFXColor newCol, bool RGB );

    static void clearBuffer (LFXBuffer& buffer);
    static void clearBuffer (LFXBuffer* buffer);

    static void writeToStream (LFXBuffer& buffer, std::ofstream& stream);
    static LFXBuffer initFromData (const int row, const int column, char * data, const int size);

    static LFXBuffer extractColour (LFXBuffer& buffer, LFXColor colour, bool rgb);
    static bool compareColours (LFXColor a, LFXColor b, bool rgb);
    
    const int totalRows;
    const int totalColums;
    
private:
    LFXColor  * data;
    const int dataSize;
    bool blendColours;
};


#endif /* defined(__Crayon__LFXBuffer__) */
