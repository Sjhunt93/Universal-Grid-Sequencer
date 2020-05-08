//
//  Clock.cpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#include "Clock.hpp"


Clock::Clock ()
{
    currentTick = 0;
    isPlaying = false;
    tickLimit = 1;
}
Clock::Clock (const float bpm)
{
    isPlaying = false;
    setBpm(bpm);
}
void Clock::setBpm (const float _bpm)
{
    bpm = _bpm;
    const double value = (60.0/ ((double) _bpm)) / 8.0;
    tickLimit = value * 1000;
    currentTick = 0;
    
}

void Clock::pulse ()
{
    currentTick += 1.0;
    if (currentTick > tickLimit) {
        
        
        //listnerList.call(&OGController::clockPulse, 0 , 0,0,0);
        listnerList.call(&OGController::clockPulse, _32_counter/8, _32_counter/4, _32_counter/2, _32_counter);
        
        _32_counter++;
        if (_32_counter >= 32) {
            _32_counter = 0;
        }
        
        currentTick -= tickLimit;
    }

}

void Clock::addController (OGController * controller)
{
    listnerList.add(controller);
}
void Clock::removeController (OGController * controller)
{
    listnerList.remove(controller);
}
void Clock::setTransport (eState state)
{
    if (state == eState::ePlay) {
        isPlaying = true;
    }
    else if (state == eState::ePause) {
        isPlaying = false;
    }
    else if (state == eState::eRestart) {
        _32_counter = 0;
        currentTick = 0;
    }
    
}
