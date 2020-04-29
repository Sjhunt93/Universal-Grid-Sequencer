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
#include "GridModelMap.h"



class PadGrid : public Component, public Pad::Listner {
public:
    
    
    PadGrid ();
    PadGrid (GridModelMap * map);
    ~PadGrid ();
    
    void paint (Graphics & g);
    void resized ();
    
    std::vector<Pad *> pads;
    
    void objectDropped (const int x, const int y, Array<var> data, const Pad::Listner::eDropType type);
    
private:
    GridModelMap * modelMap;
    ControllerBase controler;
};



#endif /* defined(__MusicGrid__PadGrid__) */
