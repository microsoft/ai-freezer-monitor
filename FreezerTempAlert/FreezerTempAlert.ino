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

#include "cls.h"

temp_sensor tmp;
alert_handler alert;
database adafruitIO;
SimpleTimer alertTimer(6e5);

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting...");
    adafruitIO.init();
    tmp.init();    
}

void loop()
{
    // Set the temperature you want to be alerted at
    // Default temperature is -50 celsius
    const float thresholdTemperature = -50;

    Serial.println(tmp.temperature());
    adafruitIO.write(tmp.temperature());

    if (tmp.temperature() >= thresholdTemperature && alertTimer.elapsed() >= alertTimer.interval)
    {
        alert.send();
        alertTimer.start();
        
    }
    delay(5000);
}