//
//  PadGrid.cpp
//  MusicGrid
//
//  Created by Samuel Hunt on 14/11/2017.
//
//

#include "PadGrid.h"


PadGrid::PadGrid ()
{
    for (int i = 0; i < 64; i++) {
        pads.push_back(new Pad(*this));
        addAndMakeVisible(pads[i]);
        pads[i]->x = i % 8;
        pads[i]->y = i / 8;
    }
}
PadGrid::~PadGrid ()
{
    
}

void PadGrid::paint (Graphics & g)
{
    g.fillAll(Colours::lightcyan);
}
void PadGrid::resized ()
{
    
    const float w = getWidth() / 8.0;
    const float h = getHeight() / 8.0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            //pads[j+i*8]->setBounds(j*w, h*i, w * 0.95, h * 0.95);
            pads[j+i*8]->setBounds(j*w, h*i, w, h);
        }
        
    }
    
}

void PadGrid::doSomething (int xIn, int yIn, Array<var> * data)
{
    for (int i = 0; i < 64; i++) {
        pads[i]->col = Colours::green;
    }

    std::vector<int> tpUpdate;
    bool outOfBounds = false;
    
    
    const int rootPosition = xIn+yIn*8;
    tpUpdate.push_back(rootPosition);

    
    
//    for (var a : data) {
        for (int i = 0; i < data->size(); i++) {
            String str = (*data)[i];
            const int x = xIn + str.upToFirstOccurrenceOf(",", false, false).getIntValue();
            const int y = yIn + str.fromFirstOccurrenceOf(",", false, false).getIntValue();
            bool o = (x < 0 || x >= 8) || (y < 0 || y >= 8);

            if (!o) {
                const int position = x + (y*8);
                tpUpdate.push_back(position);
            }
            outOfBounds |= o;

    }
    
    for (int i : tpUpdate) {
        pads[i]->col = outOfBounds ? Colours::red : Colours::orange;
    }

    for (int i = 0; i < 64; i++) {
        pads[i]->repaint();
    }
}