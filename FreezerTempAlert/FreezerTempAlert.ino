#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"


#include "config.h"

class temp_sensor 
{
    public:
        temp_sensor()
        {
        }
        float temperature()
        {
            float temp = _mcp.readThermocouple();
            return temp;
        }
        void init()
        {
            if (! _mcp.begin(_I2C_ADDRESS))
            {
                if (Serial){
                    Serial.println("Sensor not found");
                }
                while (1);
            }
            _mcp.setADCresolution(MCP9600_ADCRESOLUTION_18);
            _mcp.setThermocoupleType(MCP9600_TYPE_K);
            _mcp.setFilterCoefficient(3);
            _mcp.enable(true);
        }
        
       
    
    private:
        Adafruit_MCP9600 _mcp;
        uint8_t _I2C_ADDRESS = 0x67;
        
};

class database
{
    public:
        database()
        {
        }
        void write(float data)
        {
            run();
            temperature->save(data);
            if (Serial)
            {     
                Serial.print("Sending: ");
                Serial.print(data);
                Serial.println();
            }
        }
        void init()
        {
            io.connect();
            while(io.status() < AIO_CONNECTED) {
                Serial.print(".");
                Serial.print(io.status());
                delay(500);
            }
        }
        void run()
        {
            io.run();
        }

    
    private:
    AdafruitIO_Feed *temperature = io.feed("temperature");
   
};

class alert_handler
{
    public:
        alert_handler()
        {
        }
        void send()
        {
            io.run();
            temp_alert->save(1);
            temp_alert->save(0);

            if (Serial)
            {
                Serial.println("Alert Sent");
                Serial.println();
            }
            
        }
        void resetAlert()
        {
            _alertStatus == false;
            
        }
    private:
    AdafruitIO_Feed *temp_alert = io.feed("temp_alert");
    bool _alertStatus = false;
    bool _firstRun = true;
};

class SimpleTimer
{
private:
    uint64_t _start;
    uint64_t _stop;
    uint64_t _elapsed;
    uint64_t _interval;

public:
    SimpleTimer(long interval, bool readyStatus = false)
    {
        this->interval = interval;
        _ready = readyStatus;
    }
    void start()
    {
        _start = millis();
    }
    void stop()
    {
        _stop = millis();
    }
    float elapsed()
    {
        stop();
        return _stop - _start;
    }
    bool isReady()
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

    uint32_t interval;
    bool _ready;
};

temp_sensor tmp;
alert_handler alert;
database adafruitIO;
SimpleTimer alertTimer(6e4);

void setup()
{
    Serial.begin(9600);
    Serial.println("Staring...");
    adafruitIO.init();
    tmp.init();
    
}

void loop()
{
    float target = 25.4;
    Serial.println(tmp.temperature());
    adafruitIO.write(tmp.temperature());
    if (tmp.temperature() >= target && alertTimer.elapsed() >= alertTimer.interval)
    {
        alert.send();
        alertTimer.start();
        
    }
    delay(5000);
}