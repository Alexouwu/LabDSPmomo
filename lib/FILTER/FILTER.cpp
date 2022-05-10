#include "FILTER.h"
#include <Arduino.h>

FILTER::FILTER()
{
}
FILTER::~FILTER()
{
}

void FILTER::setup(float b[], float a[], int b_size, int a_size)
{
    bArrSize = b_size; 
    aArrSize = a_size;  

    for(int i=0; i < bArrSize; i++){
        _b[i] = b[i];
    }

    for(int i=0; i < aArrSize; i++){
        _a[i] = a[i];
    }

    for(int i=0; i < aArrSize; i++){
        _buffer_y[i] = 0;
    }

    for(int i=0; i < bArrSize; i++){
        _buffer_x[i] = 0;
    }

}

void FILTER::getAll()
{
    Serial.println("bArrSize");
    Serial.println(bArrSize);
    Serial.println("aArrSize");
    Serial.println(aArrSize);
    Serial.println("_b[0]");
    Serial.println(_b[0]);



}

float FILTER::filter(float input_signal)
{
    // Update input buffer
    for (int i = 0; i < bArrSize; i++)
    {
        _buffer_x[bArrSize-i] = _buffer_x[bArrSize-i-1];
    }
    _buffer_x[0] = input_signal;

    float filtered_signal_momo = 0;
   
    for(int i=0; i<bArrSize; i++)
    {
        filtered_signal_momo += _b[i] * _buffer_x[i];
    }
    

    for(int i=1; i<aArrSize; i++)
    {
        filtered_signal_momo -= _a[i] * _buffer_y[i-1];
    }


    // Update output buffer
    for (int i = 0; i < aArrSize; i++)
    {
        _buffer_y[aArrSize-i] = _buffer_y[aArrSize-i-1];
    }
    
    _buffer_y[0] = filtered_signal_momo;

    return filtered_signal_momo / _a[0];
}