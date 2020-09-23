// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// class that represents a temperature sensor

#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#define MCP9600_DEFAULT_I2C 0x67

class temp_sensor 
{
    public:
        temp_sensor(uint8_t i2c = MCP9600_DEFAULT_I2C);
        float temperature();
        void init();
    
    private:
        Adafruit_MCP9600 _mcp;
        uint8_t _i2cAddress;
        
};

#endif