/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BTClipAudioProcessor::BTClipAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), false)
                     #endif
                       ),
treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
}

BTClipAudioProcessor::~BTClipAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout BTClipAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    // Make sure to update the number of reservations after adding params
    params.reserve(5);

//    auto pPreamp = std::make_unique<juce::AudioParameterFloat>(preampSliderId, preampSliderName, -100.0f, 100.0f, 0.0f);
//    auto pPhase = std::make_unique<juce::AudioParameterBool>(phaseId, phaseName, false);
//    auto pReset = std::make_unique<juce::AudioParameterBool>(listenId, listenName, false);
//    auto pStageType = std::make_unique<juce::AudioParameterInt>(stageTypeId, stageTypeName, 0, 1, 0);
//    auto pCalibration = std::make_unique<juce::AudioParameterInt>(calibrationId, calibrationName, 0, 3, 0);
//
//    params.push_back(std::move(pPreamp));
//    params.push_back(std::move(pPhase));
//    params.push_back(std::move(pReset));
//    params.push_back(std::move(pStageType));
//    params.push_back(std::move(pCalibration));

   return { params.begin(), params.end() };
}

//==============================================================================
const juce::String BTClipAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BTClipAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BTClipAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BTClipAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BTClipAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BTClipAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BTClipAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BTClipAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BTClipAudioProcessor::getProgramName (int index)
{
    return {};
}

void BTClipAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BTClipAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BTClipAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BTClipAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BTClipAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

}

//==============================================================================
bool BTClipAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BTClipAudioProcessor::createEditor()
{
    return new BTClipAudioProcessorEditor (*this);
}

//==============================================================================
void BTClipAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream (stream);
}

void BTClipAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    treeState.state = tree;
    
    m_WindowWidth = variableTree.getProperty("width");
    m_WindowHeight = variableTree.getProperty("height");
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BTClipAudioProcessor();
}
