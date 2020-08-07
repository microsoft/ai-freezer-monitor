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