#include "FILTER.h"

FILTER::FILTER()
{
}
FILTER::~FILTER()
{
}

void FILTER::setup(float b[], float a[], int order)
{
    int bArrSize = sizeof(b)/sizeof(b[0]);
    int aArrSize = sizeof(a)/sizeof(a[0]);
    _order = order;

    for(int i=0; i < bArrSize; i++){
        _b[i] = b[i];
    }

    for(int i=0; i < aArrSize; i++){
        _a[i] = a[i];
    }

    for(int i=0; i < order; i++){
        _buffer_x[i] = 0;
        _buffer_y[i] = 0;
    }
}

float FILTER::filter(float input_signal)
{
    for(int i=0; i<_order-1; i++)
    {
        _buffer_x[i+1] = _buffer_x[i];
    }

    _buffer_x[0] = input_signal;

    float filtered_signal_momo = 0;
    for(int i=0; i<_order; i++)
    {
        filtered_signal_momo += _b[i] * _buffer_x[i];
    }
        for(int i=0; i<_order; i++)
    {
        filtered_signal_momo -= _a[i] * _buffer_y[i];
    }

    for(int i=0; i<_order-1; i++)
    {
        _buffer_y[i+1] = _buffer_y[i];
    }
    
    _buffer_y[0] = filtered_signal_momo;

    return filtered_signal_momo;
}