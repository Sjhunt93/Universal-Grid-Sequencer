//
//  LFXBuffer.cpp
//  Crayon
//
//  Created by Samuel Hunt on 23/07/2015.
//
//

#include "LFXBuffer.h"


LFXBuffer::LFXBuffer (const int rows, const int columns) :
totalRows(rows),
totalColums(columns),
dataSize(rows * columns)
{
    data = new LFXColor[dataSize]();
    for (int i = 0; i < dataSize; i++) {
        data[i].clearColor();
    }
    blendColours = false;
}

LFXBuffer::LFXBuffer (const LFXBuffer& other) :
totalRows(other.totalRows),
totalColums(other.totalColums),
dataSize(totalRows * totalColums)
{
    data = new LFXColor[dataSize]();
    for (int i = 0; i <dataSize; i++) {
        data[i] = other.data[i];
    }
    blendColours = false;
}
LFXBuffer::~LFXBuffer ()
{
    delete [] data;
}

void LFXBuffer::setBufferBlend (const bool blend)
{
    blendColours = blend;
}

LFXColor& LFXBuffer::colorForIndex (const int index)
{
    jassert(index < dataSize);
    return data[index];
}
LFXColor& LFXBuffer::colorForPostion (const int row, const int column)
{
    jassert(row < totalRows && row >= 0);
    jassert(column < totalColums && column >= 0);
    return data[row * totalColums + column];
}

inline LFXColor blendRGB (LFXColor old, LFXColor newInput)
{
    
    if ((old.colorRGB[0] + old.colorRGB[1] + old.colorRGB[2]) == 0 ) { //we dont want to blend with nothing...
        return newInput;
    }
    else if ((newInput.colorRGB[0] + newInput.colorRGB[1] + newInput.colorRGB[2]) == 0 )
    {
        return old;
    }
    
    const uint8 red = (old.colorRGB[0] + newInput.colorRGB[0]) / 2;
    const uint8 green = (old.colorRGB[1] + newInput.colorRGB[1]) / 2;
    const uint8 blue = (old.colorRGB[2] + newInput.colorRGB[2]) / 2;
    
    return LFXColor(red, green, blue);
}

void LFXBuffer::writeToIndex (LFXColor input, const int index)
{
    jassert(index < dataSize);

    
    data[index] = blendColours ? blendRGB(data[index], input) : input;
//    data[index] = input;
}
void LFXBuffer::writeToPosition (LFXColor input, const int row, const int column)
{
    jassert(row < totalRows && row >= 0);
    jassert(column < totalColums && column >= 0);
    const int index = row * totalColums + column;
    data[index] = blendColours ? blendRGB(data[index], input) : input;

//    data[row * totalColums + column] = input;
}
void LFXBuffer::writeToPositionXY (LFXColor input, const int x, const int y, bool blend)
{
    jassert(y < totalRows && y >= 0);
    jassert(x < totalColums && x >= 0);
    const int index = y * totalColums + x;
    data[index] = (blendColours && blend) ? blendRGB(data[index], input) : input;

//    data[y * totalColums + x] = input;
}

bool LFXBuffer::writeOptimised (LFXColor input, const int x, const int y)
{
    jassert(y < totalRows && y >= 0);
    jassert(x < totalColums && x >= 0);
    const int index = y * totalColums + x;
    if (compareColours(input, data[index], true)) {
        return false;
    }
    else {
        data[index] = input;
    }
    return true;
}
bool LFXBuffer::check (const int x, const int y)
{
    if (y < totalRows && y >= 0 ) {
        if ((x < totalColums && x >= 0)) {
            return true;
        }
    }
    return false;
}
void LFXBuffer::blendWithBuffer (LFXBuffer other)
{
    for (int i = 0; i <dataSize; i++) {
        data[i] = blendRGB(data[i], other.data[i]);
//        for (int colComp = 0; colComp < 3; colComp++) {
//            data[i].colorRGB[colComp] = ((data[i].colorRGB[colComp] + other.data[i].colorRGB[colComp]) / 2);
//        }
    }
}

void LFXBuffer::blendWithColor (LFXColor color)
{
    for (int i = 0; i <dataSize; i++) {
        if (data[i].colorRGB[0] + data[i].colorRGB[1] + data[i].colorRGB[2] == 0) {
            continue;
        }
        data[i] = blendRGB(data[i], color);
        //        for (int colComp = 0; colComp < 3; colComp++) {
        //            data[i].colorRGB[colComp] = ((data[i].colorRGB[colComp] + other.data[i].colorRGB[colComp]) / 2);
        //        }
    }
}



void LFXBuffer::operator=(const LFXBuffer& other)
{
    jassert(other.totalColums == totalColums && other.totalRows == totalRows);
    for (int i = 0; i <dataSize; i++) {
        data[i] = other.data[i];
    }
}


void LFXBuffer::shiftGridLR (int value)
{
//    bool incDir = value > 0;
//    value = abs(value);
    if (value > 8) {
        value = 8;
    }
    if (value < -8) {
        value = -8;
    }
    
    
//    LFXBuffer copy(*this);
    LFXBuffer blank (totalRows, totalColums);
//    const int dir = incDir ? 1 : -1;
//    for (int i = 0; i < value; i++) {
//        for (int row = 0; i < totalRows; i++) {
////            blank.writeToPosition(, <#const int row#>, <#const int column#>)
//        }
//    }

    for (int col = 0; col < totalColums; col++) {
        for (int row = 0; row < totalRows ; row++) {
            int writePosCol = col + value;
            if (writePosCol >= 0 && writePosCol < totalColums) {
                blank.writeToPosition(colorForPostion(row, col), row, writePosCol);
            }
//            blank.writeToPosition(<#LFXColor input#>, <#const int row#>, <#const int column#>)
        }
    }
    this->operator=(blank);
}
void LFXBuffer::shiftGridUD (int value)
{
    if (value > 8) {
        value = 8;
    }
    if (value < -8) {
        value = -8;
    }
    
    LFXBuffer blank (totalRows, totalColums);

    
    for (int row = 0; row < totalRows ; row++) {
        for (int col = 0; col < totalColums; col++) {
            int writePosRow = row + value;
            if (writePosRow >= 0 && writePosRow < totalRows) {
                blank.writeToPosition(colorForPostion(row, col), writePosRow, col);
            }

        }
    }
    this->operator=(blank);
}

void LFXBuffer::replaceColour (LFXColor old, LFXColor newCol, bool RGB )
{
    for (int i = 0; i < dataSize; i++) {
        if ((compareColours(data[i], old, RGB))) {
            data[i] = newCol;
        }
    }
}


/*static*/void LFXBuffer::clearBuffer (LFXBuffer& buffer)
{
    for (int i = 0; i < buffer.dataSize; i++) {
        buffer.data[i].clearColor();
    }
}
/*static*/ void LFXBuffer::clearBuffer (LFXBuffer* buffer)
{
    for (int i = 0; i < buffer->dataSize; i++) {
        buffer->data[i].clearColor();
    }
}

/*static*/ void LFXBuffer::writeToStream (LFXBuffer& buffer, std::ofstream& stream)
{
    stream.write((char *) buffer.data, buffer.dataSize*sizeof(LFXColor));
}
/*static*/ LFXBuffer LFXBuffer::initFromData (const int row, const int column, char * data, const int size)
{
    LFXBuffer buffer(row, column);
    for (int i = 0; i < size; i+= 4) {
        buffer.data[i/4].colorRG = data[i];
        buffer.data[i/4].colorRGB[0] = data[i + 1];
        buffer.data[i/4].colorRGB[1] = data[i + 2];
        buffer.data[i/4].colorRGB[2] = data[i + 3];
    }
    return buffer;
}

/*static*/ LFXBuffer LFXBuffer::extractColour (LFXBuffer& buffer, LFXColor colour, bool rgb)
{
    LFXBuffer newBuffer (buffer);
    for (int i = 0; i < buffer.dataSize; i++) {
        if (! (compareColours(buffer.data[i], colour, rgb))) {
            newBuffer.data[i].clearColor();

        }
    }
    return newBuffer;
}
/*static*/ bool LFXBuffer::compareColours (LFXColor a, LFXColor b, bool rgb)
{
    if (rgb) {
        if (a.colorRGB[0] != b.colorRGB[0]) {
            return false;
        }
        if (a.colorRGB[1] != b.colorRGB[1]) {
            return false;
        }
        if (a.colorRGB[2] != b.colorRGB[2]) {
            return false;
        }
        return true;
    }
    else {
        return a.colorRG == b.colorRG;
    }
    return false;
}
