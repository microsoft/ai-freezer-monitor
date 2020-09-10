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

#if __has_include("config.h")
#include "config.h"
#else
#error Your configuration file missing. Go to aka.ms/freezerconfig for instruction on how to add this file.
#endif

temp_sensor::temp_sensor(uint8_t address)
{
    _i2cAddress = address;
}
float temp_sensor::temperature()
{
    float temp = _mcp.readThermocouple();
    return temp;
}
void temp_sensor::init()
{
    if (! _mcp.begin(_i2cAddress))
    {
        if (Serial)
        {
            Serial.println("Sensor not found");
        }
        while (1);
    }
    _mcp.setADCresolution(MCP9600_ADCRESOLUTION_18);
    _mcp.setThermocoupleType(MCP9600_TYPE_K);
    _mcp.setFilterCoefficient(3);
    _mcp.enable(true);
}

database::database()
{
    temperature = io.feed("temperature"); 
}
void database::init()
{
    io.connect();
    while(io.status() < AIO_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
}

void database::write(float data)
    {
        io.run();
        temperature->save(data);
        if (Serial)
        {     
            Serial.print("Sending: ");
            Serial.print(data);
            Serial.println();
        }
    }


void database::run()
{
    io.run();
}

alert_handler::alert_handler()
{
    temp_alert = io.feed("temp_alert");
}

void alert_handler::send()
{
    io.run();
    temp_alert->save(1);

    if (Serial)
    {
        Serial.println("Alert Sent");
        Serial.println();
    }
            
}

SimpleTimer::SimpleTimer(long interval, bool readyStatus)
{
    this->interval = interval;
    _ready = readyStatus;
}

void SimpleTimer::start()
{
    _start = millis();
}
    
void SimpleTimer::stop()
{
    _stop = millis();
}

float SimpleTimer::elapsed()
{
    stop();
    return _stop - _start;
}

bool SimpleTimer::isReady()
{
    if (this->elapsed() >= this->interval || _ready == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}