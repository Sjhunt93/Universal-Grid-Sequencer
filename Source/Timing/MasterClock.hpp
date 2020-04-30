//
//  MasterClock.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef MasterClock_hpp
#define MasterClock_hpp


// manages lots of clocks.
// this runs on its own thread


// so the clock threads drive the controllers, LED feedback and MIDI out is written to a buffer.

//at some point the locks are synced and messages are output.

#include "../JuceLibraryCode/JuceHeader.h"
#include <array>


class MasterClock : public Thread {
public:
    
    MasterClock ();
    ~MasterClock ();
    
    void run();
    
    
    std::function<void()> frameBufferCallback;
    std::function<void()> _1msCallback;
    
    
};


#endif /* MasterClock_hpp */
