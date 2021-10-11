/*
  ==============================================================================

    InitMenu.cpp
    Created: 10 Oct 2021 1:46:17pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void BTClipAudioProcessorEditor::init_Menu()
{
    addAndMakeVisible(m_ClipMenu);
    menuAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState, driveModelId, m_ClipMenu);
    m_ClipMenu.addItem("Soft", 1);
    m_ClipMenu.addItem("Hard", 2);
    m_ClipMenu.addItem("Analog", 3);
}
