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

    setSize (400, 300);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    threshSlider.setBounds(100, 0, 200, 50);
    ratioSlider.setBounds(100, 50, 200, 50);
    kneeSlider.setBounds(100, 100, 200, 50);
    attackSlider.setBounds(100, 150, 200, 50);
    releaseSlider.setBounds(100, 200, 200, 50);
}

void MncompressorAudioProcessorEditor::addSlider(String _name, String _id, String _labelText, Slider& _slider, Label& _label, std::unique_ptr<SliderAttachment>& _attachment)
{
    _attachment = std::make_unique<SliderAttachment>(processor.treeState, _id, _slider);
    _label.setText(_labelText, dontSendNotification);
    _label.attachToComponent(&_slider, true);
    addAndMakeVisible(_slider);
}
