/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class MncompressorAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MncompressorAudioProcessorEditor (MncompressorAudioProcessor&);
    ~MncompressorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MncompressorAudioProcessor& processor;
    //AudioProcessorValueTreeState& params;

    Slider threshSlider;
    Slider ratioSlider;
    Slider kneeSlider;
    Slider attackSlider;
    Slider releaseSlider;

    Label threshLabel;
    Label ratioLabel;
    Label kneeLabel;
    Label attackLabel;
    Label releaseLabel;

    std::unique_ptr<SliderAttachment> threshAttachment;
    std::unique_ptr<SliderAttachment> ratioAttachment;
    std::unique_ptr<SliderAttachment> kneeAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    void MncompressorAudioProcessorEditor::addSlider(String _name, String _id, String _labelText, Slider& _slider, Label& _label, std::unique_ptr<SliderAttachment>& _attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MncompressorAudioProcessorEditor)
};
