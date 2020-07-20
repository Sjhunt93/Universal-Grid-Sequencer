/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"



//==============================================================================
MainContentComponent::MainContentComponent() : modelMap({9,9})
//sequencer8(16,12,120)
//sequencer8(15,13,11, 130)
{
    pg = std::make_unique<PadGrid>(&modelMap);
    addAndMakeVisible(pg.get());
    
    addAndMakeVisible(t);
    setSize (800, 800);
    
    
  

        
        std::vector<double> tickAmounts;
        
        auto findSmallest = [&]() -> int {
            int small = 0;
            for (int i = 1; i < tickAmounts.size(); i++) {
                if (tickAmounts[i] < tickAmounts[small]) {
                    small = i;
                }
            }
            return small;
        };
        
        auto comapreAll = [&]() -> bool {
            double last = tickAmounts[0];
            bool result = false;
            for (int i = 1; i < tickAmounts.size(); i++) {
                double current = tickAmounts[i];
                if (fabs(last-current) <= 0.01) { //basically everything has to be more-or-less the same.
                    result = true;
                }
                else {
                    result = false;
                }
                last = current;
            }
            return result;
        };
        
        std::vector<double> tickIncrements;
    
    tickAmounts.push_back(2000);
    tickIncrements.push_back(2000);
    
    tickAmounts.push_back(1983.4710743802);
    tickIncrements.push_back(1983.4710743802);
    
    
        
        for (int i = 0; i < 1000000; i++) {
            
            if (comapreAll()) {
                const float result = tickAmounts[0];
                std::cout << "resync after: " << i << "pulses, or: " << result / 1000.0 << "seconds \n";
                break;
            }
            
            const int smallestindex = findSmallest();
            tickAmounts[smallestindex] += tickIncrements[smallestindex];
            
        }
        std::cout << "No sync for clock count:\n";



    
    //---------------------------------------------------------------------------------------------------------------------------------------

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
