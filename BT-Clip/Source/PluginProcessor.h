/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LV_HardClipper.h"
#include "LV_SoftClipper.h"
#include "PedalDistortion.h"
#include "LV_SVFilter.h"

#define filterToggleId "filter toggle"
#define filterToggleName "Filter Toggle"

#define phaseId "phase toggle"
#define phaseName "Phase Toggle"

#define driveModelId "drive model"
#define driveModelName "Drive Model"

#define inputSliderId "input slider"
#define inputSliderName "Input Slider"

#define outputSliderId "output slider"
#define outputSliderName "Output Slider"

#define cutoffSliderId "cutoff slider"
#define cutoffSliderName "Cutoff Slider"

#define midGainSliderId "mid gain"
#define midGainSliderName "Mid Gain"

#define driveSliderId "drive slider"
#define driveSliderName "Drive Slider"


//==============================================================================
/**
*/
class BTClipAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    BTClipAudioProcessor();
    ~BTClipAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /**Value Trees*/
    juce::AudioProcessorValueTreeState treeState;
    
    juce::ValueTree variableTree
    { "Variables", {},
      {
        { "Group", {{ "name", "RMS Vars" }},
          {
              { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}}
          }
        }
      }
    };
    
    /**Window Vars*/
    float m_WindowWidth {0.0f};
    float m_WindowHeight {0.0f};

private:
    
    /**Parameters*/
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    /**DSP*/
    LV_HardClipper m_HardClipperModule;
    LV_SoftClipper m_SoftClipperModule;
    PedalDistortion m_AnalogClipperModule;
    LV_SVFilter m_MidToneModule;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BTClipAudioProcessor)
};
