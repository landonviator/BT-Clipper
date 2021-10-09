/*
  ==============================================================================

    PositionComponents.cpp
    Created: 9 Oct 2021 2:26:37am
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void BTClipAudioProcessorEditor::position_components()
{
    float l_Width = AudioProcessorEditor::getWidth();
    float l_Height = AudioProcessorEditor::getHeight();
    float l_LeftMargin = l_Width * 0.25;
    float l_TopMargin = l_Height * 0.25;
    float l_DialSize = l_Width * 0.15;
    
    for (auto i {0}; i < sliders.size(); i++)
    {
        if (i == 0)
        {
            sliders[i]->setBounds(l_LeftMargin, l_TopMargin, l_DialSize, l_DialSize);
        }
        
        else
        {
            sliders[i]->setBounds(sliders[i-1]->getX() + sliders[i-1]->getWidth(), l_TopMargin, l_DialSize, l_DialSize);
        }
    }
}
