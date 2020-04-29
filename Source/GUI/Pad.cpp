//
//  Pad.cpp
//  MusicGrid
//
//  Created by Samuel Hunt on 14/11/2017.
//
//

#include "Pad.h"




Pad::Pad (Listner & l) : listner(l)
{
    col = Colours::green;
}
Pad::~Pad ()
{
    
}

void Pad::paint (Graphics & g)
{
    g.setColour(col);
    g.fillRect(0,0, getWidth(), getHeight());
    
    g.setColour(Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight());
    
}

bool Pad::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
    return true;
}
void Pad::itemDragEnter (const SourceDetails& dragSourceDetails)
{
    col = Colours::orange;
    repaint();
    listner.objectDropped(x, y, *dragSourceDetails.description.getArray(), Listner::eDropType::eTest);
}
void Pad::itemDragMove (const SourceDetails& dragSourceDetails)
{
    
}
void Pad::itemDragExit (const SourceDetails& dragSourceDetails)
{
    col = Colours::green;
        repaint();
}
void Pad::itemDropped (const SourceDetails& dragSourceDetails)
{
    listner.objectDropped(x, y, *dragSourceDetails.description.getArray(), Listner::eDropType::eDrop);
}
