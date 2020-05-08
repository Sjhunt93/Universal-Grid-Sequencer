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
#include "Clock.hpp"
#include <map>

class MasterClock : public Thread {
public:
    
    MasterClock ();
    ~MasterClock ();
    
    
    void start ();
    void run();
    
    
    std::function<void()> frameBufferCallback;
    std::function<void()> _1msCallback;
    
    
    //these must only by called when the thread is stoppped!
    
    
    const int addNewClock (float bpm);
    const int getTotalClocks ();
    Clock * getClock (const int index);
    void deleteClock (const int index);
    
    

    
    
private:
//    std::map<int, Clock *> clocks;
    std::vector<Clock *> listOfClocks;
};


#endif /* MasterClock_hpp */
