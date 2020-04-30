/*
  ==============================================================================

    MNCompressor.h
    Author:  Mirren Malcolm-Neale

  ==============================================================================
*/

#pragma once
#include "CircularBuffer.h"

class MNCompressor
{
public:
    MNCompressor();
    float CompressSample(float _data, float _thresh, float _ratio, float _attack, float _release, float _knee);
    float InterpolatePoints(float* _xPoints, float* _yPoints, float _detectedValue);

private:
    CircularBuffer buffer;
    float timeAvg;
    float rms;
    float gain;
};
