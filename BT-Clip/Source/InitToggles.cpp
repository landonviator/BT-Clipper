/*
  ==============================================================================

    InitToggles.cpp
    Created: 9 Oct 2021 2:40:08am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void BTClipAudioProcessorEditor::init_toggles()
{
    addAndMakeVisible(m_PrePostToggle);
    
    const auto message = m_PrePostToggle.getToggleState() ? "Pre" : "Post";

    m_PrePostToggle.setButtonText(message);

    m_PrePostToggle.onClick = [&]()
    {
        const auto message = m_PrePostToggle.getToggleState() ? "Pre" : "Post";

        m_PrePostToggle.setButtonText(message);
    };
}
