//
//  IODevice.h
//  OpenGrid
//
//  Created by Samuel Hunt on 11/10/2018.
//
//

#ifndef __OpenGrid__IODevice__
#define __OpenGrid__IODevice__

#include <iostream>


//Input Output device
//Can be anything, MIDI or Osc or custom
/*
 
 IODevice
    - MIDI
        - Launchpad
        - 
    - OSC
        - 
    - Other
        - etc
 
 */
class IODevice {
public:

    bool isXYActive (const int x, const int y) {return false;}
    
};

#endif /* defined(__OpenGrid__IODevice__) */
