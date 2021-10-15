/*
  ==============================================================================

    ParamsChanged.cpp
    Created: 13 Oct 2021 7:28:36pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginProcessor.h"

void BTClipAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == inputSliderId)
    {
        m_Preamp = std::powf(10.0f, newValue * 0.05f);
    }
    
    if (parameterID == outputSliderId)
    {
        m_Trim = std::powf(10.0f, newValue * 0.05f);
    }
    
    if (parameterID == cutoffSliderId)
    {
        m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kCutoff, newValue);
    }
    
    if (parameterID == midGainSliderId)
    {
        m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kGain, newValue);
    }
    
    if (parameterID == driveSliderId)
    {
        m_ClippersModule.setParameter(LV_Clippers ::ParameterId::kDrive, newValue);
    }
    
    if (parameterID == filterToggleId)
    {
        m_PostEq = newValue;
    }
    
    if (parameterID == phaseId)
    {
        m_Phase = newValue;
    }
    
    if (parameterID == driveModelId)
    {
        m_Drive_Type = newValue;
        if (newValue == 0)
        {
            m_ClippersModule.set_clipping_type(LV_Clippers::ClippingType::kHardClip);

//            if (m_Drive <= 24.0)
//            {
//                treeState.getParameterAsValue(outputSliderId) = -m_Drive;
//            }
//
//            else
//            {
//                treeState.getParameterAsValue(outputSliderId) = -24.0;
//            }
        }

        else if (newValue == 1)
        {
            m_ClippersModule.set_clipping_type(LV_Clippers::ClippingType::kSoftClip);

//            if (m_Drive <= 26.0)
//            {
//                treeState.getParameterAsValue(outputSliderId) = -m_Drive;
//            }
//
//            else
//            {
//                treeState.getParameterAsValue(outputSliderId) = -26.0;
//            }
        }

        else
        {
            m_ClippersModule.set_clipping_type(LV_Clippers::ClippingType::kAnalog);

//            if (m_Drive <= 28.0)
//            {
//                treeState.getParameterAsValue(outputSliderId) = -m_Drive;
//            }
//
//            else
//            {
//                treeState.getParameterAsValue(outputSliderId) = -28.0;
//            }
        }
    }
}

