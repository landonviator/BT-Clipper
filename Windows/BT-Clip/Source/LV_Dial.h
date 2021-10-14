/*
  ==============================================================================

    LV_Dial.h
    Created: 20 Jul 2021 9:43:18pm
    Author:  landon viator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce
{

class LV_Dial : public Slider
{
public:
    
    LV_Dial(juce::String suffix, double rangeStart, double rangeEnd, double intervalValue, double returnValue)
    {
        setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
        setTextBoxStyle(Slider::TextBoxBelow, false, 96, 32);
        setRange(rangeStart, rangeEnd, intervalValue);
        setDoubleClickReturnValue(true, returnValue);
        setTextValueSuffix(suffix);
        setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(Slider::ColourIds::thumbColourId));
        setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colour::fromRGB(35, 35, 35));
        setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black.withAlpha(0.0f));
        setColour(Slider::ColourIds::textBoxTextColourId, Colours::whitesmoke.withAlpha(0.25f));
    }
    
private:

    
    
};
}
