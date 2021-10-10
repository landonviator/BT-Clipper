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
    addAndMakeVisible(m_InputSlider);
    m_InputSlider.setLookAndFeel(&customSlider);
    m_InputSlider.setComponentEffect(&sliderShadow);
    
    addAndMakeVisible(m_OutputSlider);
    m_OutputSlider.setLookAndFeel(&customSlider);
    m_OutputSlider.setComponentEffect(&sliderShadow);
    
    for (auto i {0}; i < sliders.size(); i++)
    {
        addAndMakeVisible(sliders[i]);
        sliders[i]->setLookAndFeel(&customDial);
        sliders[i]->setComponentEffect(&dialShadow);
    }
}
