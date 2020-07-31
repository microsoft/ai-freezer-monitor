#include "cls.h"

temp_sensor tmp;
alert_handler alert;
database adafruitIO;
SimpleTimer alertTimer(6e5);

void setup()
{
    Serial.begin(9600);
    Serial.println("Staring...");
    adafruitIO.init();
    tmp.init();    
}

void loop()
{
    // Set the temperature you want to be alerted at
    const float thresholdTemperature = -50;

    Serial.println(tmp.temperature());
    Serial.println("After Reading");
    adafruitIO.write(tmp.temperature());
    Serial.println("sent");
    if (tmp.temperature() >= thresholdTemperature && alertTimer.elapsed() >= alertTimer.interval)
    {
        alert.send();
        alertTimer.start();
        
    }
    delay(5000);
}