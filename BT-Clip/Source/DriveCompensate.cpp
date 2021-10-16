/*
  ==============================================================================

    DriveCompensate.cpp
    Created: 14 Oct 2021 7:49:00pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void BTClipAudioProcessorEditor::drive_compensation()
{
    
    m_OutputSlider.setValue(m_DriveDial.getValue() * -0.56);
}
