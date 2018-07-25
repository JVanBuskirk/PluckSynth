/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluckSynth  : public AudioProcessorEditor
{
public:
    //==============================================================================
    PluckSynth (PluckSynthAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluckSynth();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluckSynthAudioProcessor& processor;
    MidiKeyboardComponent keyboardComponent;
    AudioProcessorValueTreeState& valueTreeState;

    ScopedPointer<SliderAttachment> durAttachment;
    ScopedPointer<SliderAttachment> cutAttachment;
    ScopedPointer<SliderAttachment> ampAttachment;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> dur;
    std::unique_ptr<Slider> cut;
    std::unique_ptr<Slider> amp;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluckSynth)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
