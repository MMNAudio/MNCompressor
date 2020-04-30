/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MncompressorAudioProcessor::MncompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
    , treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.state = ValueTree(THRESH_ID);
    treeState.state = ValueTree(RATIO_ID);
    treeState.state = ValueTree(KNEE_ID);
    treeState.state = ValueTree(ATTACK_ID);
    treeState.state = ValueTree(RELEASE_ID);
}

MncompressorAudioProcessor::~MncompressorAudioProcessor()
{
}

//** Initialise paramaters **//
AudioProcessorValueTreeState::ParameterLayout MncompressorAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    auto threshParam = std::make_unique<AudioParameterFloat>(THRESH_ID, THRESH_NAME, NormalisableRange<float>(-60.0f, 20.0f, 0.01f), 10.0f);
    auto ratioParam = std::make_unique<AudioParameterFloat>(RATIO_ID, RATIO_NAME, NormalisableRange<float>(1.0f, 20.0f, 0.01f), 2.0f);
    auto kneeParam = std::make_unique<AudioParameterFloat>(KNEE_ID, KNEE_NAME, NormalisableRange<float>(0.0f, 24.0f, 0.01f), 0.0f);
    auto attackParam = std::make_unique<AudioParameterFloat>(ATTACK_ID, ATTACK_NAME, NormalisableRange<float>(0.01f, 500.0f, 0.01f), 100.0f);
    auto releaseParam = std::make_unique<AudioParameterFloat>(RELEASE_ID, RELEASE_NAME, NormalisableRange<float>(0.01f, 2000.0f, 0.01f), 500.0f);

    params.push_back(std::move(threshParam));
    params.push_back(std::move(ratioParam));
    params.push_back(std::move(kneeParam));
    params.push_back(std::move(attackParam));
    params.push_back(std::move(releaseParam));

    return { params.begin(), params.end() };
}

//==============================================================================
const String MncompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MncompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MncompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MncompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MncompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MncompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MncompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MncompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String MncompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MncompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MncompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int channel = 0; channel < getNumOutputChannels(); channel++)
    {
        allCompressors.add(MNCompressor());
    }
}

void MncompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MncompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void MncompressorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
        {
            auto* data = buffer.getWritePointer(channel);
            MNCompressor* compressor = &allCompressors.getReference(channel);
            data[i] = compressor->CompressSample(data[i], -30.0f, 20.0f, 0.01f, 0.4f, 0.0f);
        }
    }
}

//==============================================================================
bool MncompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MncompressorAudioProcessor::createEditor()
{
    return new MncompressorAudioProcessorEditor (*this);
}

//==============================================================================
void MncompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MncompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid())
    {
        treeState.state = tree;
    }


}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MncompressorAudioProcessor();
}
