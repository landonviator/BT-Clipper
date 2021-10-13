/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LV_Dial.h"
#include "LV_Label.h"
#include "LV_Toggle.h"
#include "StyleSheet.h"
#include "LV_Menu.h"
#include "LV_Fader.h"

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
    void set_up_window(BTClipAudioProcessor &audioProcessor);
    
    /**Bug with the resized function finishing before the constructor, this bool helps fix it*/
    bool constructorFinished = false;
    
    /**Sliders*/
    juce::LV_Fader m_InputSlider {" dB", -24.0, 24.0, 0.25, 0.0};
    juce::LV_Fader m_OutputSlider {" dB", -24.0, 24.0, 0.25, 0.0};
    juce::LV_FaderLAF customSlider;
    
    /**Dials*/
    juce::LV_Dial m_CutoffDial {" Hz", 300.0, 5000.0, 1.0, 300.0};
    juce::LV_Dial m_MidToneGain {" dB", -10.0, 10.0, 0.25, 0.0};
    juce::LV_Dial m_DriveDial {" dB", 0.0, 24.0, 0.25, 0.0};
    std::vector<juce::Slider*> sliders {&m_CutoffDial, &m_MidToneGain, &m_DriveDial};
    void init_dials();
    void set_dial_props();
    juce::LV_AlphaDialLAF customDial;
    
    /**Slider attachments*/
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> inputSliderAttach, outputSliderAttach, cutoffSliderAttach,
    midGainSliderAttach, driveSliderAttach;
    
    /**Labels*/
    juce::LV_Label m_CutoffLabel {"Cutoff"};
    juce::LV_Label m_MidToneGainLabel {"Gain"};
    juce::LV_Label m_DriveLabel {"Drive"};
    juce::LV_Label m_InputLabel {"Input"};
    juce::LV_Label m_OutputLabel {"Output"};
    std::vector<juce::Label*> labels {&m_CutoffLabel, &m_MidToneGainLabel, &m_DriveLabel};
    void init_labels();
    
    /**Toggles*/
    juce::LV_Toggle m_PrePostToggle;
    juce::LV_Toggle m_Phase;
    void extracted();
    
    /**Button attachments*/
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> filterEngageButtonAttach, phaseButtonAttach;
    
    void init_toggles();
    void set_pre_post_toggle_props();
    void set_phase_toggle_props();
    
    /**Menu*/
    juce::LV_Menu m_ClipMenu {"Clip Voice"};
    void init_Menu();
    
    /**Slider attachments*/
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> menuAttach;
    
    /**Position Components*/
    void position_components();
    
    /**Save Window Size*/
    void save_window_size();
    
    /**Image background*/
    juce::Image pluginBackground;
    void paint_background(juce::Graphics &g);
    
    /**Clean Memory*/
    void clean_memory();
    
    /**Shadows*/
    /**Initialize shadows*/
    void init_shadows();
    
    /**Dial shadow*/
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    /**Fader shadow*/
    juce::DropShadow sliderShadowProperties;
    juce::DropShadowEffect sliderShadow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BTClipAudioProcessorEditor)
};
