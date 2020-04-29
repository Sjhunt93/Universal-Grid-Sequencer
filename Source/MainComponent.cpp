/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : modelMap({9,9})
{
    pg = new PadGrid(&modelMap);
    addAndMakeVisible(pg);
    
    addAndMakeVisible(t);
    setSize (800, 800);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    pg->setBounds(10, 10, getWidth() * 0.48, getHeight() * 0.48);
    
    t.setBounds(getWidth() * 0.5 + 50, 50, 50, 50);
}
