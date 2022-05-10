#ifndef _FILTER_H
#define _FILTER_H

#define _MAX 5

class FILTER
{
private:
    float _b[_MAX];
    float _a[_MAX];
    int bArrSize, aArrSize;
    float _buffer_x[_MAX];
    float _buffer_y[_MAX];

public:
    FILTER();
    ~FILTER();
    void setup(float b[], float a[], int b_size, int a_size);
    float filter(float input_signal);
    void getAll();
};

#endif