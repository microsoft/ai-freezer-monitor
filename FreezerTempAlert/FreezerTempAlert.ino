// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// This program read the temperature using a thermocouple and uploads it to an
// online database. If temperature goes above a specific threshold it triggers
// a warning. This is part of a bigger project that can be found at 
// https://github.com/microsoft/ai-freezer-monitor. The code is designed to
// work on Adafruit's Huzzah32, but should work on any ESP32 dev board.

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