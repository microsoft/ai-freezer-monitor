// Copyright (c) Microsoft Corporation. All Rights Reserved.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the Software), to deal 
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
// IN THE SOFTWARE

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