// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// all classes used in program

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