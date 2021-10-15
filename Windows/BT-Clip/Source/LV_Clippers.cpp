/*
  ==============================================================================

    LV_SoftClipper.cpp
    Created: 8 Jul 2021 3:08:32pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "LV_Clippers.h"


void LV_Clippers::reset()
{
    preamp = 0.0;
    trim = 1.0;
    blend = 1.0;
    drive = 1.0f;
    piDivisor = 2 / 3.1415926;
    
    powerState = true;
}

void LV_Clippers::prepare(juce::dsp::ProcessSpec spec)
{
    currentSampleRate = spec.sampleRate;
}

float LV_Clippers::processSample(float input)
{
    // Don't process signal if the module isn't enabled
    if (!powerState) return input;
    
    switch (m_ClipType)
    {
        case ClippingType::kHardClip:
        {
            input *= drive;
            
            // Hard clipper
            if (input >= thresh)
            {
                output = thresh;
            }
                
            else if (input <= -thresh)
            {
                output = -thresh;
            }
                
            else
            {
                output = input;
            }
            
        } break;
            
        case ClippingType::kSoftClip:
        {
            // Exponential Distortion
            if (input >= 0.0)
            {
                output = 1.0 - exp(-abs(drive * input));
            }
                    
            else
            {
                output = -1.0 * (1.0 - exp(-abs(drive * input)));
            }
            
        } break;
            
        case ClippingType::kAnalog:
        {
            output = tanh((-drive - 1.0) * input + input) - tanh(pow(input, 3.0f));
            output *= 0.65;
            
        } break;
    }
    
    return output;
}

void LV_Clippers::setParameter(ParameterId parameter, float parameterValue)
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

void LV_Clippers::set_clipping_type(ClippingType clippingType)
{
    m_ClipType = clippingType;
}


float LV_Clippers::getPreamp()
{
    return preamp;
}

float LV_Clippers::getBias()
{
    return bias;
}

float LV_Clippers::getTrim()
{
    return trim;
}

float LV_Clippers::getBlend()
{
    return blend;
}

float LV_Clippers::getSampleRate()
{
    return currentSampleRate;
}

bool LV_Clippers::getPowerState()
{
    return powerState;
}
