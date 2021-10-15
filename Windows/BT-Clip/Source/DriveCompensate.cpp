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
    if (m_ClipMenu.getSelectedId() < 3)
    {
        if (m_DriveDial.getValue() <= 21.0f)
        {
            m_OutputSlider.setValue(m_DriveDial.getValue() * -1.0);
        }
    }
    
    else
    {
        if (m_DriveDial.getValue() <= 28.0f)
        {
            m_OutputSlider.setValue(m_DriveDial.getValue() * -1.0);
        }
    }
}
