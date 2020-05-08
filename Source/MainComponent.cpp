/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() :  deviceManager({2,2}), modelMap({9,9})
{
    pg = std::make_unique<PadGrid>(&modelMap);
    addAndMakeVisible(pg.get());
    
    addAndMakeVisible(t);
    setSize (800, 800);
    

    
    deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {0,0}, "Launchpad Mini", "Launchpad Mini");
    deviceManager.deviceAtPosInVector({0,0})->setOrientation(OGDevice::eOrientation::eRotatedLeft);
    
    
    deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {1,0}, "Launchpad Mini 2", "Launchpad Mini 2");
    deviceManager.deviceAtPosInVector({1,0})->offset = {9,0};
    
    deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {0,1}, "Launchpad Mini 3", "Launchpad Mini 3");
    deviceManager.deviceAtPosInVector({0,1})->setOrientation(OGDevice::eOrientation::eRotated180);
    deviceManager.deviceAtPosInVector({0,1})->offset = {0,9};
    
    deviceManager.createNewDevice(OGDeviceManager::eDeviceType::eLaunchpadRG, {1,1}, "Launchpad Mini 4", "Launchpad Mini 4");
    deviceManager.deviceAtPosInVector({1,1})->setOrientation(OGDevice::eOrientation::eRotatedRight);
    deviceManager.deviceAtPosInVector({1,1})->offset = {9,9};
    
    deviceManager.createMap();
    
    session = std::make_unique<OGSession>(deviceManager, mClock);
    
    mClock.frameBufferCallback = [this]()
    {
        deviceManager.collectLFXBuffers(session.get());
    };
    mClock._1msCallback = [this]()
    {
        deviceManager.dispatchBufferToControllers(session.get());
    };
    
    mClock.sendMidiMessage = [this](MidiMessage m)
    {
        deviceManager.sendMidiMessageMaster(m);
    };
    
    mClock.addNewClock(120);
    mClock.getClock(0)->addController(session->controllerForIndex(0));
//    mClock.getClock(0)->addController(session->controllerForIndex(1));
    
    mClock.start();
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
