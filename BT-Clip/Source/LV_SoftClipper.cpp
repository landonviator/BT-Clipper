/*
  ==============================================================================

    LV_SoftClipper.cpp
    Created: 8 Jul 2021 3:08:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_SoftClipper.h"


void LV_SoftClipper::reset()
{
    preamp = 0.0;
    trim = 1.0;
    blend = 1.0;
    drive = 1.0f;
    piDivisor = 2 / 3.1415926;
    
    powerState = true;
}

void LV_SoftClipper::prepare(juce::dsp::ProcessSpec spec)
{
    currentSampleRate = spec.sampleRate;
}

float LV_SoftClipper::processSample(float input)
{
    // Don't process signal if the module isn't enabled
    if (!powerState) return input;
    
    // Exponential Distortion
    if (input >= 0.0)
    {
        output = 1.0 - exp(-abs(drive * input));
    }
            
    else
    {
        output = -1.0 * (1.0 - exp(-abs(drive * input)));
    }
    
    return output;
}

void LV_SoftClipper::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter) {
            
        case ParameterId::kPreamp:
        {
            // Should be in dB
            preamp = parameterValue; break;
        }
            
        case ParameterId::kBias:
        {
            // Should be bewteen 0 and 1
            bias = parameterValue; break;
        }
            
        case ParameterId::kDrive:
        {
            // Should be in dB
            drive = pow(10.0f, parameterValue * 0.05f); break;
        }
            
        case ParameterId::kTrim:
        {
            // Should be in dB
            trim = pow(10.0, parameterValue / 20.0); break;
        }
            
        case ParameterId::kBlend:
        {
            // Should be in %
            blend = juce::jmap(parameterValue, 0.0f, 100.0f, 0.0f, 1.0f); break;
        }
            
        case ParameterId::kSampleRate:
        {
            currentSampleRate = parameterValue; break;
        }
    }
}


float LV_SoftClipper::getPreamp()
{
    return preamp;
}

float LV_SoftClipper::getBias()
{
    return bias;
}

float LV_SoftClipper::getTrim()
{
    return trim;
}

float LV_SoftClipper::getBlend()
{
    return blend;
}

float LV_SoftClipper::getSampleRate()
{
    return currentSampleRate;
}

bool LV_SoftClipper::getPowerState()
{
    return powerState;
}
