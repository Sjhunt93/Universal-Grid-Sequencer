//
//  InputBuffer.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 30/04/2020.
//
//

#ifndef InputBuffer_hpp
#define InputBuffer_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include <array>
#include "OGDevice.hpp"

struct InputBuffer {
    
    InputBuffer ()
    {
        writePosA = 0;
        readPos = 0;
    }
    //this is thread safe
    void addMessage (OGDevice::OGInMsg msg)
    {
        //add mutex.
        buffer[writePosA] = msg;
        writePosA++;
        if (writePosA >= buffer.size())
        {
            writePosA = 0;
        }
    }
    int clearBuffer (std::array<OGDevice::OGInMsg, 50> & bufferOut)
    {
        //add mutex
        int i = 0;
        int writePos = writePosA; //at this point the addMessage thread is free to contiue.
        for (;  writePos < readPos ? readPos < buffer.size() : readPos < writePos ; readPos++)
        {
            OGDevice::OGInMsg msg = buffer[readPos];
            //std::cout << msg.getDescription() << "\n";
            bufferOut[i] = msg;
            i++;
            
        }
        
        if (readPos >= buffer.size()) {
            readPos = 0;
        }
        for (; readPos < writePos; readPos++) {
            OGDevice::OGInMsg msg = buffer[readPos];
            bufferOut[i] = msg;
            i++;
           // std::cout << msg.getDescription() << "\n";
        }
        return i;
        //readPos--;
    }
    
    std::array<OGDevice::OGInMsg, 50> buffer; //complete guess for size.
    std::atomic<int> writePosA;
    int readPos;
    
};

#endif /* InputBuffer_hpp */
