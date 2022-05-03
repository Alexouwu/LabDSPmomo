#ifndef _FILTER_H
#define _FILTER_H

#include <vector>

class FILTER
{
private:
    float _b[];
    float _a[];
    int _order;
    int bArrSize, aArrSize;
    float _buffer_x[4];
    float _buffer_y[4];

public:
    FILTER();
    ~FILTER();
    void setup(float b[], float a[], int order, int b_size, int a_size);
    float filter(float input_signal);
};

#endif