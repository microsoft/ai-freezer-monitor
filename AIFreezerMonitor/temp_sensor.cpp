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
