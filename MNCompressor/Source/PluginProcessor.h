/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MNCompressor.h"

#define THRESH_ID "threshold"
#define THRESH_NAME "Threshold"
#define RATIO_ID "ratio"
#define RATIO_NAME "Ratio"
#define KNEE_ID "knee"
#define KNEE_NAME "Knee"
#define ATTACK_ID "attack"
#define ATTACK_NAME "Attack"
#define RELEASE_ID "release"
#define RELEASE_NAME "Release"

//==============================================================================
/**
*/
class MncompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MncompressorAudioProcessor();
    ~MncompressorAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState treeState;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:
    Array<MNCompressor> allCompressors;
   

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MncompressorAudioProcessor)
};
