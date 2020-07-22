#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"
#include "AdafruitIO_WiFi.h"


#ifndef CLS_H_
#define CLS_H_

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

class database
{
    public:
        database();
        void write(float data);
        void init();
    
    private:
        AdafruitIO_Feed *temperature;
        void run();
   
};

class alert_handler
{
    public:
        alert_handler();
        void send();
    private:
    AdafruitIO_Feed *temp_alert;
};

class SimpleTimer
{
private:
    uint64_t _start;
    uint64_t _stop;
    uint64_t _elapsed;
    uint64_t _interval;

public:
    SimpleTimer(long interval, bool readyStatus = false);
    void start();
    void stop();
    float elapsed();
    bool isReady();
    uint32_t interval;

    private:
        bool _ready;
};

#endif