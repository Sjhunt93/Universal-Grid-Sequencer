//
//  PadGrid.h
//  MusicGrid
//
//  Created by Samuel Hunt on 14/11/2017.
//
//

#ifndef __MusicGrid__PadGrid__
#define __MusicGrid__PadGrid__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pad.h"




class PadGrid : public Component, public Pad::Listner {
public:
    
    
    PadGrid ();
    ~PadGrid ();
    
    void paint (Graphics & g);
    void resized ();
    
    std::vector<Pad *> pads;
    
    
    void doSomething (int x, int y, Array<var> * data);
};



#endif /* defined(__MusicGrid__PadGrid__) */
