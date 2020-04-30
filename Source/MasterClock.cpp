//
//  MasterClock.cpp
//  OpenGrid - App
//
//  Created by Samuel Hunt on 4/29/20.
//

#include "MasterClock.hpp"


MasterClock::MasterClock () : Thread("Master Clock")
{
    startThread();
}
MasterClock::~MasterClock ()
{
    stopThread(3000);
}

void MasterClock::run()
{
    int64 last = Time::getMillisecondCounterHiRes();
    int64 current = last;
    int64 dif = 0;
    
    int bfCounter = 0; //this the counter for keeping track of writing to the buffer.
    const int screenthreshold = 20;
    while (!threadShouldExit()) {
        
        current = Time::getMillisecondCounterHiRes();
        dif = current - last;
        if (dif > 1) { //fire every 1ms.
            bfCounter++;
            if (bfCounter >= screenthreshold) {
                bfCounter = 0;
                //now lets clear the buffer.
                std::cout << "frame \n";
            }
            
            last = current;
            // fire clocks to all controllers
            
            // get a clear the MIDI buffer
            
        }
        
        // this stops the threead running like madman.....
        usleep(100);
        
    }
}
