/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluckSynthAudioProcessor::PluckSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters (*this, nullptr)

{
    parameters.createAndAddParameter ("dur",       // parameterID
                                      "duration",       // parameter name
                                      String(),     // parameter label (suffix)
                                      NormalisableRange<float> (0.1f, 20.0f),    // range
                                      1.0f,         // default value
                                      nullptr,
                                      nullptr);
                                      
    parameters.createAndAddParameter ("cut",       // parameterID
                                      "Filter Cutoff",       // parameter name
                                      String(),     // parameter label (suffix)
                                      NormalisableRange<float> (100.0f, 15000.0f),    // range
                                      7000.0f,         // default value
                                      nullptr,
                                      nullptr);
                                      
    parameters.createAndAddParameter ("amp",       // parameterID
                                      "Amplitude",       // parameter name
                                      String(),     // parameter label (suffix)
                                      NormalisableRange<float> (0.00f, 1.0f),    // range
                                      0.4f,         // default value
                                      nullptr,
                                      nullptr);
                                      
    parameters.state = ValueTree (Identifier ("APVTSPluck"));
}

PluckSynthAudioProcessor::~PluckSynthAudioProcessor()
{
}

//==============================================================================
const String PluckSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluckSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluckSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluckSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluckSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluckSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluckSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluckSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String PluckSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluckSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluckSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    keyboardState.reset();
    pyo.setup(getTotalNumOutputChannels(), samplesPerBlock, sampleRate);
    pyo.exec(BinaryData::PluckSynthJuce_py);
    // initialisation that you need..
}

void PluckSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    keyboardState.reset();
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluckSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluckSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    MidiMessage m;
    int time;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
        {
            pyo.midi(143+m.getChannel(), m.getNoteNumber(), m.getVelocity());
        }
        else if (m.isNoteOff())
        {
            pyo.midi(127+m.getChannel(), m.getNoteNumber(), m.getVelocity());
        }
        else if (m.isController())
        {
            pyo.midi(175+m.getChannel(), m.getControllerNumber(), m.getControllerValue());
        }
        else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }
    }
    
    pyo.value("dur", *parameters.getRawParameterValue ("dur"));
    pyo.value("cut", *parameters.getRawParameterValue ("cut"));
    pyo.value("amp", *parameters.getRawParameterValue ("amp"));
    
    pyo.process(buffer);
}

//==============================================================================
bool PluckSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluckSynthAudioProcessor::createEditor()
{
    return new PluckSynth (*this, parameters);
}

//==============================================================================
void PluckSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
        copyXmlToBinary (*xml, destData);
}

void PluckSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

        if (xmlState != nullptr)
            if (xmlState->hasTagName (parameters.state.getType()))
                parameters.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluckSynthAudioProcessor();
}
