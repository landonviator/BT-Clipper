/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LV_Dial.h"
#include "StyleSheet.h"

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
    
    /**Dials*/
    juce::LV_Dial m_CutoffDial {" Hz", 300.0, 5000.0, 1.0, 300.0};
    juce::LV_Dial m_QDial {" Q", 0.05, 0.95, 0.05, 0.3};
    juce::LV_Dial m_DriveDial {" dB", 0.0, 24.0, 0.25, 0.0};
    std::vector<juce::Slider*> sliders {&m_CutoffDial, &m_QDial, &m_DriveDial};
    juce::LV_AlphaDialLAF customDial;
    
    
    /**Image background*/
    juce::Image pluginBackground;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BTClipAudioProcessorEditor)
};
