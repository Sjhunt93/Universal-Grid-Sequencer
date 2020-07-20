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
    queSize = 0;
    que.resize(50);
    for (auto & ob : que) {
        ob.isActive = false;
        ob.delay = 0;
        ob.start = 0;
    }
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
        if (dif >= 1) { //fire every 1ms.
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
            if (queSize) {
                sendAndClearQue();
            }
            
        }
        
        // this stops the threead running like madman.....
        usleep(100);
        
    }
}



const int MasterClock::addNewClock (float bpm)
{
    listOfClocks.push_back(new Clock(bpm));
    
//    double tickSync = 1;
//    for (auto * clock : listOfClocks) {
//        tickSync = tickSync * clock->getTickLimit();
//    }
//    std::cout << "Tick Sync : " << tickSync << "\n";
    calculateSyncPoint();
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
void MasterClock::queMidiMessage (MidiMessage msg, int delay)
{
    if (delay > 0) {
        for (int i = 0; i < que.size(); i++) {
            if (!que[i].isActive) {
                que[i].delay = delay;
                que[i].m = msg;
                que[i].start = Time::getMillisecondCounterHiRes();
                que[i].isActive = true;
                queSize++;
                break;
                
            }
        }
    }
}
void MasterClock::sendAndClearQue ()
{
    const int time = Time::getMillisecondCounterHiRes();
    for (int i = 0; i < que.size(); i++) {
        if (que[i].isActive) {
            if (time > (que[i].start + que[i].delay)) {
                que[i].isActive = false;
                sendMidiMessage(que[i].m);
                queSize--;
            }
        }
    }
}
void MasterClock::setTransportForAllClocks (Clock::eState state)
{
    for (auto * c : listOfClocks) {
        c->setTransport(state);
    }
}
void MasterClock::calculateSyncPoint ()
{
    
    
    if (getTotalClocks() <= 1) {
        return;
    }
    
    std::vector<double> tickAmounts;
    
    auto findSmallest = [&]() -> int {
        int small = 0;
        for (int i = 1; i < tickAmounts.size(); i++) {
            if (tickAmounts[i] < tickAmounts[small]) {
                small = i;
            }
        }
        return small;
    };
    
    auto comapreAll = [&]() -> bool {
        double last = tickAmounts[0];
        bool result = false;
        for (int i = 1; i < tickAmounts.size(); i++) {
            double current = tickAmounts[i];
            if (fabs(last-current) <= 0.01) { //basically everything has to be more-or-less the same.
                result = true;
            }
            else {
                result = false;
            }
            last = current;
        }
        return result;
    };
    
    std::vector<double> tickIncrements;


    for (auto * clock : listOfClocks) {
        tickIncrements.push_back(clock->getTickLimit());
        tickAmounts.push_back(clock->getTickLimit());
    }
    
    for (int i = 0; i < 1000000; i++) {
        
        if (comapreAll()) {
            const float result = tickAmounts[0];
            std::cout << "resync after: " << i << "pulses, or: " << result / 1000.0 << "seconds \n";
            return;
        }
        
        const int smallestindex = findSmallest();
        tickAmounts[smallestindex] += tickIncrements[smallestindex];
        
    }
    std::cout << "No sync for clock count:\n";
    
}
