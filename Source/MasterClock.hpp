//
//  MasterClock.hpp
//  OpenGrid - App
//
//  Created by Samuel Hunt on 4/29/20.
//

#ifndef MasterClock_hpp
#define MasterClock_hpp

#include "../JuceLibraryCode/JuceHeader.h"
#include <array>


class MasterClock : public Thread {
public:
    
    MasterClock ();
    ~MasterClock ();
    
    void run();
};


struct InputBuffer {
    
    InputBuffer ()
    {
        writePosA = 0;
        readPos = 0;
    }
    //this is thread safe
    void addMessage (MidiMessage msg)
    {
        //add mutex.
        buffer[writePosA] = msg;
        writePosA++;
        if (writePosA >= buffer.size())
        {
            writePosA = 0;
        }
    }
    void clearBuffer ()
    {
        //add mutex
        int writePos = writePosA; //at this point the addMessage thread is free to contiue.
        for (;  writePos < readPos ? readPos < buffer.size() : readPos < writePos ; readPos++)
        {
            MidiMessage msg = buffer[readPos];
            std::cout << msg.getDescription() << "\n";
        }
        
        if (readPos >= buffer.size()) {
            readPos = 0;
        }
        for (; readPos < writePos; readPos++) {
            MidiMessage msg = buffer[readPos];
            std::cout << msg.getDescription() << "\n";
        }
        //readPos--;
    }
    
    std::array<MidiMessage, 4> buffer;
    std::atomic<int> writePosA;
    int readPos;
    
};

#endif /* MasterClock_hpp */
