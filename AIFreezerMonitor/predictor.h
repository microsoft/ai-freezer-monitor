// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// Utilities used to process data for ML

#ifndef PREDICTOR_H_
#define PREDICTOR_H_

float normalize(float value, float min, float max);
float meanOf(float *value, int array_size);
float mae(float *x, float *y, int array_size);

#endif