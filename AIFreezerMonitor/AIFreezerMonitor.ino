// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// This program read the temperature using a thermocouple, aggregates one hour
// of data, and runs that data through a machine learning model to detected 
// anomalies in the temperature data. This is part of a bigger project that can
// be found at https://github.com/microsoft/ai-freezer-monitor. The code is 
// designed to work on Adafruit's Huzzah32, but should work on any ESP32 dev 
// board.

#include <TensorFlowLite_ESP32.h>

#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "model_data.h"

#include "predictor.h"
#include "temp_sensor.h"
#include "database.h"

// There is testing and debugging code included in this program. These should
// stay commeneted out for general use of the temperature monitor. It can be
// useful to test the model the first time the monitor is set up to make sure
// it's working as expected.

// #define TESTING
// #define DEBUG

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

// Create an area of memory to use for input, output, and intermediate arrays.
const int kModelArenaSize = 8 * 1024;
// Extra headroom for model + alignment + future interpreter changes.
const int kExtraArenaSize = 560 + 16 + 100;
const int kTensorArenaSize = kModelArenaSize + kExtraArenaSize;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

// Variables from training notebook
const int input_size = 720;
const float threshold = 0.077;
const float min_val = -21.75;
const float max_val = 4.3125;
#ifndef TESTING
float x_val[input_size];
#endif
int accumulator = 0;
temp_sensor tmp;
database temperature("temperature");
database alert("temp_alert");

#ifdef DEBUG
database error("MAE");
#endif

void setup(){
    // Set up logging
    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;

    // Map the model into a usable data structure. This doesn't involve any
    // copying or parsing, it's a very lightweight operation.
    model = tflite::GetModel(model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
            error_reporter->Report(
            "Model provided is schema version %d not equal "
            "to supported version %d.",
            model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }
    // This pulls in all the operation implementations we need.
    static tflite::ops::micro::AllOpsResolver resolver;

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        error_reporter->Report("AllocateTensors() failed");
        return;
    }

    // Obtain pointers to the model's input and output tensors.
    input = interpreter->input(0);
    output = interpreter->output(0);

    Serial.begin(9600);

    // Initialize the temperature sensor and databases.
    tmp.init();
    temperature.init();
    alert.init();
    #ifdef DEBUG
    error.init();
    #endif
}

#ifdef TESTING
float x_val[] = {};
#endif

void loop()
{   
    #ifndef TESTING

    // Gathers an hours worth of temperature readings from the sensor
    // We also continue to record specific temperatures in our database
    for (int i = 0; i < input_size; i++)
    {
        x_val[i] = tmp.temperature();
        temperature.write(x_val[i]);
        delay(5000);
    }

    #endif

    // Normalizes the data based on the variables from the training notebook
    for (int i = 0; i< input_size; i++)
    {
        x_val[i] = normalize(x_val[i], min_val, max_val);       
    }


    // Copy the data to the input tensor pointer
    for (int i = 0; i < input_size; i++)
    {
        input->data.f[i] = x_val[i];
    }

    // Run inference, and report any error
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
        error_reporter->Report("Invoke failed on x_val: %f\n",
                               static_cast<float*>(x_val));
        return;
    }
    float y_val[input_size];
    
    // Read the predicted y value from the model's output tensor
    for (int i = 0; i < input_size; i++)
    {
        y_val[i] = output->data.f[i];
    }

    float sampleMae = mae(x_val, y_val, input_size);

    if (Serial)
    {
        Serial.print("Mean Absolute Error: ");
        Serial.println(sampleMae, 4);
        #ifdef DEBUG
        error.write(sampleMae);
        #endif
    }

    if (sampleMae > threshold){
        accumulator += 1;
    }
    else if (sampleMae <= threshold)
    {
        accumulator -= 2;
        if (accumulator < 0)
        {
            accumulator = 0;
        }
    }

    if (accumulator > 4)
    {
        Serial.println("anomaly detected");
        alert.write(accumulator);
    }

}
