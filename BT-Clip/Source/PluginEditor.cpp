/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BTClipAudioProcessorEditor::BTClipAudioProcessorEditor (BTClipAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setUpWindow(audioProcessor);
    
    for (auto i {0}; i < sliders.size(); i++)
    {
        addAndMakeVisible(sliders[i]);
        sliders[i]->setLookAndFeel(&customDial);
    }
}

BTClipAudioProcessorEditor::~BTClipAudioProcessorEditor()
{
    for (auto i {0}; i < sliders.size(); i++)
    {
        sliders[i]->setLookAndFeel(nullptr);
    }
}

//==============================================================================
void BTClipAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Image layer from Illustrator
    pluginBackground = juce::ImageCache::getFromMemory(BinaryData::pluginBackground2_png, BinaryData::pluginBackground2_pngSize);
    
    // Draw and position the image
    g.drawImageWithin(pluginBackground, 0, 0, AudioProcessorEditor::getWidth(), AudioProcessorEditor::getHeight(), juce::RectanglePlacement::stretchToFit);
}

void BTClipAudioProcessorEditor::resized()
{
    float l_Width = AudioProcessorEditor::getWidth();
    float l_Height = AudioProcessorEditor::getHeight();
    float l_LeftMargin = l_Width * 0.25;
    float l_TopMargin = l_Height * 0.25;
    float l_DialSize = l_Width * 0.15;
    
    for (auto i {0}; i < sliders.size(); i++)
    {
        if (i == 0)
        {
            sliders[i]->setBounds(l_LeftMargin, l_TopMargin, l_DialSize, l_DialSize);
        }
        
        else
        {
            sliders[i]->setBounds(sliders[i-1]->getX() + sliders[i-1]->getWidth(), l_TopMargin, l_DialSize, l_DialSize);
        }
    }
    
    // Save plugin size in value tree
    audioProcessor.variableTree.setProperty("width", getWidth(), nullptr);
    audioProcessor.variableTree.setProperty("height", getHeight(), nullptr);
}
