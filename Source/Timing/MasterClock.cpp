//
//  MasterClock.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "MasterClock.hpp"
MasterClock::MasterClock () : Thread("Master Clock")
{
    
}
MasterClock::~MasterClock ()
{
    stopThread(3000);
    for (int i = 0; i < listOfClocks.size(); i++) {
        delete listOfClocks[i];
    }
}

void MasterClock::start ()
{
    startThread();
}

void MasterClock::run()
{
    int64 last = Time::getMillisecondCounterHiRes();
    int64 current = last;
    int64 dif = 0;
    
    int bfCounter = 0; //this the counter for keeping track of writing to the buffer.
    const int screenthreshold = 10;
    while (!threadShouldExit()) {
        
        current = Time::getMillisecondCounterHiRes();
        dif = current - last;
        if (dif > 1) { //fire every 1ms.
            bfCounter++;
            if (bfCounter >= screenthreshold) {
                bfCounter = 0;
                //now lets clear the buffer.
//                std::cout << "frame \n";
                if (frameBufferCallback != nullptr) {
                    frameBufferCallback();
                }
            }
            
            last = current;
            // fire clocks to all controllers
            {
                for (int i = 0; i < listOfClocks.size(); i++) {
                    listOfClocks[i]->pulse();
                }
            }
            
            
            // get a clear the MIDI buffer
            if (_1msCallback != nullptr) {
                _1msCallback();
            }
            
        }
        
        // this stops the threead running like madman.....
        usleep(100);
        
    }
}



const int MasterClock::addNewClock (float bpm)
{
    listOfClocks.push_back(new Clock(bpm));
    return getTotalClocks();
}
const int MasterClock::getTotalClocks ()
{
    return (int)listOfClocks.size();
}
Clock * MasterClock::getClock (const int index)
{
    if (index >= 0 && index < getTotalClocks()) {
        return listOfClocks[index];
    }
    return nullptr;
}
void MasterClock::deleteClock (const int index)
{
    if (index >= 0 && index < getTotalClocks()) {
        delete listOfClocks[index];
        listOfClocks[index] = nullptr;
    }
}
