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
    drive = 0.0;
    
    bias = 0.0;
    
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
    
    auto x_n = input + bias;
    
    switch(clipperType)
    {
        case 0:
        {
            // Drive for this algorithim needs to be between 0 and 1
            auto driver = juce::jmap(drive, 0.0f, 24.0f, 0.0f, 1.0f);
            
            // Cubic distortion
            output = x_n - driver * pow(x_n, 3.0);
            
            // Trim the output
            output *= trim;
                        
            break;
        }
            
        case 1:
        {
            // Arctan Distortion
            output = piDivisor * atan(x_n * pow(10.0, drive * 0.05));
            
            // Auto compensate the output as a function of the drive
            output *= trim * pow(10.0, -drive * 0.05);
                        
            break;
        }
            
        case 2:
        {
            // Drive for this algorithim needs to be between 1 and 10
            auto driver = juce::jmap(drive, 0.0f, 24.0f, 1.0f, 10.0f);
            
            // Exponential Distortion
            if (x_n >= 0.0)
            {
                output = 1.0 - exp(-abs(driver * x_n));
            }
            
            else
            {
                output = -1.0 * (1.0 - exp(-abs(driver * x_n)));
            }
            
            // Auto compensate the output as a function of the drive
            output *= trim * pow(10.0, -drive * 0.025);
                        
            break;
        }
    }
    
    // Return blended output
    return x_n * (1.0 - blend) + (output - bias) * blend;
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
            drive = parameterValue; break;
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

void LV_SoftClipper::setClippingType(ClippingType clippingType)
{
    switch (clippingType) {
            
        case ClippingType::kCubicDistortion:
        {
            clipperType = 0; break;
        }
            
        case ClippingType::kArctanDistortion:
        {
            clipperType = 1; break;
        }
            
        case ClippingType::kExponentialDistortion:
        {
            clipperType = 2; break;
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
