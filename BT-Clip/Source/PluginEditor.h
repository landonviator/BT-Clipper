/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BTClipAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BTClipAudioProcessorEditor (BTClipAudioProcessor&);
    ~BTClipAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    BTClipAudioProcessor& audioProcessor;
    void setUpWindow(BTClipAudioProcessor &audioProcessor);
    
    /**Bug with the resized function finishing before the constructor, this bool helps fix it*/
    bool constructorFinished = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BTClipAudioProcessorEditor)
};
