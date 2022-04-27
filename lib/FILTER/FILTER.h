#ifndef _FILTER_H
#define _FILTER_H

class FILTER
{
private:
    float _b[];
    float _a[];
    int _order;
    float _buffer_x[];
    float _buffer_y[];

public:
    FILTER();
    ~FILTER();
    void setup(float b[], float a[], int order);
    float filter(float input_signal);
};