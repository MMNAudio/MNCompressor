/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MncompressorAudioProcessorEditor::MncompressorAudioProcessorEditor (MncompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    addSlider(THRESH_NAME, THRESH_ID, THRESH_NAME, threshSlider, threshLabel, threshAttachment);
    addSlider(RATIO_NAME, RATIO_ID, RATIO_NAME, ratioSlider, ratioLabel, ratioAttachment);
    addSlider(KNEE_NAME, KNEE_ID, KNEE_NAME, kneeSlider, kneeLabel, kneeAttachment);
    addSlider(ATTACK_NAME, ATTACK_ID, ATTACK_NAME, attackSlider, attackLabel, attackAttachment);
    addSlider(RELEASE_NAME, RELEASE_ID, RELEASE_NAME, releaseSlider, releaseLabel, releaseAttachment);

    threshSlider.setTextValueSuffix(" dB");
    ratioSlider.setTextValueSuffix(" : 1");
    kneeSlider.setTextValueSuffix(" dB");
    attackSlider.setTextValueSuffix(" ms");
    releaseSlider.setTextValueSuffix(" ms");

    setSize (400, 600);
}

MncompressorAudioProcessorEditor::~MncompressorAudioProcessorEditor()
{
}

//==============================================================================
void MncompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void MncompressorAudioProcessorEditor::resized()
{
    threshSlider.setBounds((getWidth() / 2) - 25, 50, 100, 100);
    ratioSlider.setBounds((getWidth() / 2) - 25, 150, 100, 100);
    kneeSlider.setBounds((getWidth() / 2) - 25, 250, 100, 100);
    attackSlider.setBounds((getWidth() / 2) - 25, 350, 100, 100);
    releaseSlider.setBounds((getWidth() / 2) - 25, 450, 100, 100);
}

void MncompressorAudioProcessorEditor::addSlider(String _name, String _id, String _labelText, Slider& _slider, Label& _label, std::unique_ptr<SliderAttachment>& _attachment)
{
    addAndMakeVisible(_slider);
    _attachment = std::make_unique<SliderAttachment>(processor.treeState, _id, _slider);
    _label.setText(_labelText, dontSendNotification);
    _label.attachToComponent(&_slider, true);
    _slider.setSliderStyle(Slider::SliderStyle::Rotary);
    _slider.setTextBoxStyle(Slider::TextBoxBelow, true, 70, 20);
    _slider.setColour(Slider::textBoxOutlineColourId, Colour::Colour());
}
