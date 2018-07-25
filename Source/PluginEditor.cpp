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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluckSynth::PluckSynth (PluckSynthAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard), valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    addAndMakeVisible (keyboardComponent);
    //[/Constructor_pre]

    dur.reset (new Slider ("dur"));
    addAndMakeVisible (dur.get());
    dur->setRange (0.1, 20, 0);
    dur->setSliderStyle (Slider::LinearHorizontal);
    dur->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);

    dur->setBounds (16, 75, 288, 24);

    cut.reset (new Slider ("cut"));
    addAndMakeVisible (cut.get());
    cut->setRange (100, 15000, 0);
    cut->setSliderStyle (Slider::LinearHorizontal);
    cut->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);

    cut->setBounds (16, 115, 288, 24);

    amp.reset (new Slider ("amp"));
    addAndMakeVisible (amp.get());
    amp->setRange (0, 1, 0);
    amp->setSliderStyle (Slider::LinearHorizontal);
    amp->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);

    amp->setBounds (16, 155, 288, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 285);


    //[Constructor] You can add your own custom stuff here..
    durAttachment = new SliderAttachment (valueTreeState, "dur", *dur);
    cutAttachment = new SliderAttachment (valueTreeState, "cut", *cut);
    ampAttachment = new SliderAttachment (valueTreeState, "amp", *amp);
    //[/Constructor]
}

PluckSynth::~PluckSynth()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    durAttachment = nullptr;
    cutAttachment = nullptr;
    ampAttachment = nullptr;
    //[/Destructor_pre]

    dur = nullptr;
    cut = nullptr;
    amp = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluckSynth::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff044669));

    {
        float x = 1.0f, y = 50.0f, width = 398.0f, height = 150.0f;
        Colour fillColour = Colour (0xff044669);
        Colour strokeColour = Colour (0xff05b5ff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 2.500f);
    }

    {
        int x = 5, y = 10, width = 154, height = 30;
        String text (TRANS("Pluck Synth"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (30.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 310, y = 70, width = 58, height = 30;
        String text (TRANS("Duration"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 310, y = 110, width = 74, height = 30;
        String text (TRANS("Filter Freq."));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 310, y = 150, width = 74, height = 30;
        String text (TRANS("Amplitude"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluckSynth::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    Rectangle<int> area (getLocalBounds());
    {
        keyboardComponent.setBounds (area.removeFromBottom (80).reduced(8));
    }
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluckSynth" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="PluckSynthAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p), processor(p), keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard), valueTreeState (vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="285">
  <BACKGROUND backgroundColour="ff044669">
    <ROUNDRECT pos="1 50 398 150" cornerSize="10.00000000000000000000" fill="solid: ff044669"
               hasStroke="1" stroke="2.5, mitered, butt" strokeColour="solid: ff05b5ff"/>
    <TEXT pos="5 10 154 30" fill="solid: fff0f8ff" hasStroke="0" text="Pluck Synth"
          fontname="Default font" fontsize="30.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="310 70 58 30" fill="solid: fff0f8ff" hasStroke="0" text="Duration"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="310 110 74 30" fill="solid: fff0f8ff" hasStroke="0" text="Filter Freq."
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="310 150 74 30" fill="solid: fff0f8ff" hasStroke="0" text="Amplitude"
          fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
          bold="0" italic="0" justification="33"/>
  </BACKGROUND>
  <SLIDER name="dur" id="909a31bebf7596eb" memberName="dur" virtualName=""
          explicitFocusOrder="0" pos="16 75 288 24" min="0.10000000000000000555"
          max="20.00000000000000000000" int="0.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="0"/>
  <SLIDER name="cut" id="982bb911fb161b8b" memberName="cut" virtualName=""
          explicitFocusOrder="0" pos="16 115 288 24" min="100.00000000000000000000"
          max="15000.00000000000000000000" int="0.00000000000000000000"
          style="LinearHorizontal" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="0"/>
  <SLIDER name="amp" id="2ce3b44f1fc01a86" memberName="amp" virtualName=""
          explicitFocusOrder="0" pos="16 155 288 24" min="0.00000000000000000000"
          max="1.00000000000000000000" int="0.00000000000000000000" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
