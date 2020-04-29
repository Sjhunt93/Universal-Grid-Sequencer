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
//    for (int i = 0; i < 64; i++) {
//        pads.push_back(new Pad(*this));
//        addAndMakeVisible(pads[i]);
//        pads[i]->x = i % 8;
//        pads[i]->y = i / 8;
//    }
}

PadGrid::PadGrid (GridModelMap * map)
{
    modelMap = map;
    
    for (int y = 0; y < modelMap->gridSize.y; y++) {
        for (int x = 0; x < modelMap->gridSize.x; x++) {
        
            pads.push_back(new Pad(*this));
            const int index = pads.size()-1;
            addAndMakeVisible(pads[index]);
            pads[index]->x = x;
            pads[index]->y = y;
            
            GridModelMap::PadModel * pad = modelMap->getPad(x, y);
            pad->pad = pads[index];
        }
    }
}
PadGrid::~PadGrid ()
{
    for (int i = 0; i < pads.size(); i++) {
        delete pads[i];
    }
}

void PadGrid::paint (Graphics & g)
{
    g.fillAll(Colours::lightcyan);
}
void PadGrid::resized ()
{
    XY xy = modelMap->gridSize;
    const float w = getWidth() / xy.x;
    const float h = getHeight() / xy.y;
    for (int i = 0; i < xy.x; i++) {
        for (int j = 0; j < xy.y; j++) {
            //pads[j+i*8]->setBounds(j*w, h*i, w * 0.95, h * 0.95);
            pads[i+j*xy.y]->setBounds(i*w, j*h, w, h);
        }
        
    }
    
}


void PadGrid::objectDropped (const int xIn, const int yIn, Array<var> data, const Pad::Listner::eDropType type)
{
    for (int i = 0; i < pads.size(); i++) {
        
//        pads[i]->col = Colours::blue;
        // we will enter a que messsage here, to do the actual update..
        //async update.
        
        
        pads[i]->col = modelMap->getPad(i)->controller == nullptr ? Colours::green : Colours::blue;
    }

    std::vector<int> tpUpdate;
    bool outOfBounds = false;
    
    XY size = modelMap->gridSize;

    
//    const int rootPosition = xIn+yIn*size.x;
//    tpUpdate.push_back(rootPosition);
    
    data.add(String(xIn-xIn) + "," + String(yIn-yIn));
    
    
//    for (var a : data) {
        for (int i = 0; i < data.size(); i++) {
//            String str = (*data)[i];
            String str = data[i];
            const int x = xIn + str.upToFirstOccurrenceOf(",", false, false).getIntValue();
            const int y = yIn + str.fromFirstOccurrenceOf(",", false, false).getIntValue();
            
            const bool o = modelMap->isOutsideGrid(x, y) || modelMap->getPad(x, y)->controller != nullptr;

            if (!o) {
                const int position = x + (y*size.x);
                tpUpdate.push_back(position);
            }
            outOfBounds |= o;

    }
    
    for (int i : tpUpdate) {
        if (type == Pad::Listner::eDrop && !outOfBounds) {
            pads[i]->col = Colours::blue;
            // we will enter a que messsage here, to do the actual update..
            //async update.
            modelMap->getPad(i)->controller = &controler;
            
        }
        else if (type == Pad::Listner::eTest) {
            pads[i]->col = outOfBounds ? Colours::red : Colours::orange;
        }
    }

    for (int i = 0; i < pads.size(); i++) {
        pads[i]->repaint();
    }
}
