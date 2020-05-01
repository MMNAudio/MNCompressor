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

    /** HARD KNEE 
    /*
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
    */

    /** SOFT KNEE **/
    if (_knee > 0 * dBRMS > (_thresh - _knee / 2.0f) && dBRMS < (_thresh + _knee / 2.0f))
    {
        float kneeBottom = _thresh - _knee / 2.0f;
        float kneeTop = _thresh + _knee / 2.0f;
        float _xPoints[2];
        float _yPoints[2];
        _xPoints[0] = kneeBottom;
        _xPoints[1] = kneeTop;
        _xPoints[1] = std::fmin(0.0f, kneeTop);
        _yPoints[0] = 0.0f;
        _yPoints[1] = slope;
        slope = InterpolatePoints(&_xPoints[0], &_yPoints[0], _thresh);
        _thresh = kneeBottom;
    }

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

float MNCompressor::InterpolatePoints(float* _xPoints, float* _yPoints, float _detectedValue) 
{
    float result = 0.0f;
    int n = 2;

    for (int i = 0; i < n; i++) {
        float term = 1.0f;
        for (int j = 0; j < n; j++)
        {
            if (j != i) {
                term *= (_detectedValue - _xPoints[j]) / (_xPoints[i] - _xPoints[j]);
            }
        }
        result += term * _yPoints[i];
    }

    return result;
}
