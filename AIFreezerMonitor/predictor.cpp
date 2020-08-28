#include "predictor.h"
#include <Arduino.h>
#include <math.h>

// int arrayLength = 720;

// float normalize(float value[])
// {
//     float mean = meanOf(value);
// }

float meanOf(float *value, int array_size)
{
    float totalValue;
    for (int i = 0; i < array_size; i++)
    {
        totalValue += value[i];
    }
    float mean = totalValue/array_size;
    return mean;
}

// float stdOf(float value, float mean)
// {
//     float std;
//     return std;
// }

float mae(float *x, float *y, int array_size)
{
    float _error[array_size];
    for(int i = 0; i < array_size; i++)
    {
        _error[i] = abs(y[i]-x[i]);
    }
    float _mae = meanOf(_error, array_size);
    return _mae;
}