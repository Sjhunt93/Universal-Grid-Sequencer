//
//  Clock.hpp
//  OpenGrid
//
//  Created by Samuel Hunt on 29/04/2020.
//
//

#ifndef Clock_hpp
#define Clock_hpp

#include <stdio.h>
#include "OGController.hpp"
//simple time divider, with a set time signature and speed


class Clock {
public:
    
    
    enum eState {
        ePause,
        ePlay,
        eRestart,
    };
    
    Clock ();
    Clock (const float bpm);
    void setBpm (const float bpm);
    //this should be called at 1ms intervals!
    void pulse ();
    
    
    
    
    
    void addController (OGController * controller);
    void removeController (OGController * controller);
    
    
    void setTransport (eState state);
    
    const float getBpm() {return bpm;}
private:
    ListenerList<OGController> listnerList;
    float currentTick;
    float tickLimit;
    int _32_counter;
    
//    std::atomic<int> isPlaying;
    bool isPlaying;
    float bpm;
    JUCE_DECLARE_NON_COPYABLE(Clock)
};

#endif /* Clock_hpp */
