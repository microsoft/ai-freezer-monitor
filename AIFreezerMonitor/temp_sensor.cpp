// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// class that represents a temperature sensor

#include "temp_sensor.h"

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
