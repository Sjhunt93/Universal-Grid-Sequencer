//
//  plan.h
//  OpenGrid
//
//  Created by Samuel Hunt on 4/29/20.
//

#ifndef plan_h
#define plan_h

#if 0


// we start with a device map
// this translates its input into XY positions (also deals with rotation)
// provides output for LED feedback.

/* --------
 
 Device Name
 Orientation 
 Mirror
 Grid Size (X,Y)
 Position
 
 Input Type:
    momentry pad
    velocity pad
    pressure pad
    continous controller
    + XY position
 
 Output Type:
    value... (Colour translated)
 
 MIDI Port
 
 
 
 ---------- */

// MIDI device -> device translator -> grid (map) -> controller
// Clock object

/*  MIDI device: (this is just really the juce MIDI stuff)
    - manages MIDI IO
 
 
 
    Device translator
        - translates inputs and outputs
 
    buffer manager
    - 
 
    device manager
        - manages all devices
    grid manager
        - manages the grid (sessions)
    grid 
        - maps each input to its controller
 
    controller
        - performs smart cations
        - recieves clock information
 
 
    colourBuffer:
    this is what all controllers write to, each controller has its own buffer. these are then are compiled into one buffer.
 this one buffer is sent back to the device manager, which keeps a copy of the buffer then only outputs what is needed each time.
 
 */



#endif




#endif /* plan_h */
