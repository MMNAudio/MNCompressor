/*
  ==============================================================================

    MNCompressor.cpp
    Author:  Mirren Malcolm-Neale

  ==============================================================================
*/

#include "MNCompressor.h"

MNCompressor::MNCompressor()
{
    buffer = CircularBuffer(150, 20);
    timeAvg = 0.01f;
    rms = 0.0f;
    gain = 1.0f;
}

float MNCompressor::CompressSample(float _data, float _thresh, float _ratio, float _attack, float _release, float _knee)
{
    //Continous power of waveform, to decibel
    rms = (1 - timeAvg) * rms + timeAvg * std::pow(_data, 2.0f);
    float dBRMS = 10 * std::log10(rms);

    //Convert given ratio (from user) to a slope value, ensure gain in db is < 0
    // convert gain to linear scale
    float slope = 1 - (1 / _ratio);
    float dbGain = std::min(0.0f, (slope * (_thresh - dBRMS)));
    float newGain = std::pow(10, dbGain / 20);

    //Smoothing values for transition
    float coeff;
    if (newGain < gain)
    {
        coeff = _attack;
    }
    else
    {
        coeff = _release;
    }

    gain = (1 - coeff) * gain + coeff * newGain;

    // Set/get values from buffer
    float compressedSample = gain * buffer.GetData();
    buffer.SetData(_data);
    buffer.NextSample();

    return compressedSample;
}
