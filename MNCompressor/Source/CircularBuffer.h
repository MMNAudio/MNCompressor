/*
  ==============================================================================

    CircularBuffer.h
    Author:  Mirren Malcolm-Neale

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class CircularBuffer
{
public:
    CircularBuffer();
    CircularBuffer(int _bufferSize, int _delayLength);
    float GetData();
    void SetData(float _data);
    void NextSample();
private:
    AudioSampleBuffer buffer;
    int writeIndex;
    int readIndex;
    int delayLength;
};
