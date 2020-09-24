// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// Utlities used to porcess data for ML

#include "predictor.h"
#include <Arduino.h>
#include <math.h>

float normalize(float value, float min, float max)
{
    float _normalizedValue = (value - min) / (max - min);

    return _normalizedValue;
}

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