/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PadGrid.h"


class Thing : public Component, public DragAndDropContainer {
    
public:
    Thing ()
    {
        
    }
    void resized ()
    {
        
    }
    void paint (Graphics & g)
    {
        g.setColour(Colours::white);
        g.fillRect(0, 0, getWidth(), getHeight());
        
    }
    void mouseDrag (const MouseEvent& event)
    {
        //        startDragging("Preset", this);
        //        printf("%i %i \n", getWidth(), getHeight());
        //        printf("Dragging %i %i \n", event.x, event.y);
        //        Point<int> point = this->getBounds().getCentre() * -1;
#if 1
        //        Point<int> point(getWidth() - 5, getHeight() - 5);
        startDragging(getPoints(), this, Image::null, true);
#else
        //        Point<int> p(0 - event.x, 0 - event.y);
        Image dragImage = this->createComponentSnapshot (this->getLocalBounds()).convertedToFormat (Image::ARGB);
        dragImage.multiplyAllAlphas (0.6f);
        Point<int> p(offsetX*0.5, offsetY*0.5);
        std::cout << p.toString() << "\n";
        startDragging("IGMSE_PART", this, dragImage, &p);
#endif
        
    }
    void mouseDown (const MouseEvent& event)
    {
        printf("Mouse Clicked \n");
        printf("Clicking %i %i \n", event.x, event.y);
        offsetX = event.x;
        offsetY = event.y;
    }
    
    
    Array<var> getPoints ()
    {
        // 8 would be replace with the row size..
        //return {1, 2};
        
        Array<var> data;
        
//        data.add("1,0");
        data.add("0,1");
        data.add("1,1");
        data.add("-1,1");
//        data.add((int) (0 + (1 << 8))); // x fow 8 bits, y for 
        
        return data;
        
//        return {1, (1*8),(1*8) + 1};
        //        return {(1*8), (1*8)-1, (1*8)+1};
    }
    
    int offsetX;
    int offsetY;
};



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    PadGrid pg;
    Thing t;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
