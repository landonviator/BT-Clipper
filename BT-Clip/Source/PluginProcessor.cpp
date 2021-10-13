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
    treeState.addParameterListener (inputSliderId, this);
    treeState.addParameterListener (outputSliderId, this);
    treeState.addParameterListener (cutoffSliderId, this);
    treeState.addParameterListener (midGainSliderId, this);
    treeState.addParameterListener (driveSliderId, this);
    treeState.addParameterListener (filterToggleId, this);
    treeState.addParameterListener (phaseId, this);
    treeState.addParameterListener (driveModelId, this);
}

BTClipAudioProcessor::~BTClipAudioProcessor()
{
    treeState.removeParameterListener (inputSliderId, this);
    treeState.removeParameterListener (outputSliderId, this);
    treeState.removeParameterListener (cutoffSliderId, this);
    treeState.removeParameterListener (midGainSliderId, this);
    treeState.removeParameterListener (driveSliderId, this);
    treeState.removeParameterListener (filterToggleId, this);
    treeState.removeParameterListener (phaseId, this);
    treeState.removeParameterListener (driveModelId, this);
}

juce::AudioProcessorValueTreeState::ParameterLayout BTClipAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    // Make sure to update the number of reservations after adding params
    params.reserve(8);

    auto p_FilterToggle = std::make_unique<juce::AudioParameterBool>(filterToggleId, filterToggleName, false);
    auto p_Phase = std::make_unique<juce::AudioParameterBool>(phaseId, phaseName, false);
    auto p_DriveModel = std::make_unique<juce::AudioParameterInt>(driveModelId, driveModelName, 0, 2, 0);
    auto p_Input = std::make_unique<juce::AudioParameterFloat>(inputSliderId, inputSliderName, -24.0, 24.0, 0.0);
    auto p_Output = std::make_unique<juce::AudioParameterFloat>(outputSliderId, outputSliderName, -24.0, 24.0, 0.0);
    auto p_Cutoff = std::make_unique<juce::AudioParameterFloat>(cutoffSliderId, cutoffSliderName, 300, 5000, 1000);
    auto p_MidGain = std::make_unique<juce::AudioParameterFloat>(midGainSliderId, midGainSliderName, -10.0, 10.0, 0.0);
    auto p_Drive = std::make_unique<juce::AudioParameterFloat>(driveSliderId, driveSliderName, 0.0, 24.0, 0.0);
    
    params.push_back(std::move(p_FilterToggle));
    params.push_back(std::move(p_Phase));
    params.push_back(std::move(p_DriveModel));
    params.push_back(std::move(p_Input));
    params.push_back(std::move(p_Output));
    params.push_back(std::move(p_Cutoff));
    params.push_back(std::move(p_MidGain));
    params.push_back(std::move(p_Drive));

   return { params.begin(), params.end() };
}

void BTClipAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == inputSliderId)
    {
        DBG("Input: " << newValue);
    }
    
    if (parameterID == outputSliderId)
    {
        DBG("Output: " << newValue);
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
        DBG("Drive: " << newValue);
    }
    
    if (parameterID == filterToggleId)
    {
        DBG("Pre/Post: " << newValue);
    }
    
    if (parameterID == phaseId)
    {
        DBG("Phase: " << newValue);
    }
    
    if (parameterID == driveModelId)
    {
        DBG("DriveModel: " << newValue);
    }
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
    // Initialize spec for dsp modules
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    m_MidToneModule.reset();
    m_MidToneModule.prepare(spec);
    m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kType, LV_SVFilter::FilterType::kBandShelf);
    m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kCutoff, *treeState.getRawParameterValue(cutoffSliderId));
    m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kQ, 0.33);
    m_MidToneModule.setParameter(LV_SVFilter::ParameterId::kGain, *treeState.getRawParameterValue(midGainSliderId));
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

    // Main DSP Loop
    auto channelBuffers = buffer.getArrayOfWritePointers();

    for (auto sample {0}; sample < buffer.getNumSamples(); sample++)
    {
        for (auto channel {0}; channel < buffer.getNumChannels(); channel++)
        {
            auto x = channelBuffers[channel][sample];

            x = m_MidToneModule.processSample(x, channel);
            
            channelBuffers[channel][sample] = x;
        }
    }
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
