/*
  ==============================================================================

    SetState.cpp
    Created: 13 Oct 2021 7:44:26pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginProcessor.h"

void BTClipAudioProcessor::set_state()
{
    m_WindowWidth = variableTree.getProperty("width");
    m_WindowHeight = variableTree.getProperty("height");
    
    m_PostEq = *treeState.getRawParameterValue(filterToggleId);
    m_Preamp = pow(10.0f, *treeState.getRawParameterValue(inputSliderId) * 0.05f);
    m_Trim = pow(10.0f, *treeState.getRawParameterValue(outputSliderId) * 0.05f);
    m_Phase = *treeState.getRawParameterValue(phaseId);
    
    m_ClippersModule.setParameter(LV_Clippers::ParameterId::kDrive, *treeState.getRawParameterValue(driveSliderId));
}
