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
    set_up_window(audioProcessor);
    init_dials();
    init_labels();
    init_toggles();
}

BTClipAudioProcessorEditor::~BTClipAudioProcessorEditor()
{
    clean_memory();
}

//==============================================================================
void BTClipAudioProcessorEditor::paint (juce::Graphics& g)
{
    paint_background(g);
}

void BTClipAudioProcessorEditor::resized()
{
    position_components();
    save_window_size();
}
