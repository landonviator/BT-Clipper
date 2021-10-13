/*
  ==============================================================================

    LV_SoftClipper.h
    Created: 8 Jul 2021 3:08:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

#ifndef LV_SoftClipper_h
#define LV_SoftClipper_h

#include <JuceHeader.h>

class LV_SoftClipper
{
public:
    
    void reset();
    
    void prepare(juce::dsp::ProcessSpec spec);
    
    float processSample(float input);
    
    enum class ParameterId {
            kPreamp,
            kBias,
            kDrive,
            kTrim,
            kBlend,
            kSampleRate
        };
    
    enum class ClippingType {
            kCubicDistortion,
            kArctanDistortion,
            kExponentialDistortion,
        };
    
    void setParameter(ParameterId parameter, float parameterValue);
    
    void setClippingType(ClippingType clippingType);
    
    float getPreamp();
    
    float getBias();
    
    float getTrim();
    
    float getBlend();
    
    float getSampleRate();
    
    bool getPowerState();
    
private:
    
    float preamp {1.0}, trim {1.0}, blend {1.0}, currentSampleRate {44100.0}, output {0.0}, drive{0.0}, piDivisor, bias;
    
    int clipperType {0};
    
    bool powerState = true;
};

#endif /* LV_SoftClipper_h */
