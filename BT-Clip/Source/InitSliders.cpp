/*
  ==============================================================================

    InitSliders.cpp
    Created: 9 Oct 2021 2:11:32am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void BTClipAudioProcessorEditor::init_dials()
{
    for (auto i {0}; i < sliders.size(); i++)
    {
        addAndMakeVisible(sliders[i]);
        sliders[i]->setLookAndFeel(&customDial);
    }
}
