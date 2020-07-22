#include "cls.h"

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
    Serial.println("temp");
    
}

void loop()
{
    float target = 25.4;
    Serial.println(tmp.temperature());
    Serial.println("After Reading");
    adafruitIO.write(tmp.temperature());
    Serial.println("sent");
    if (tmp.temperature() >= target && alertTimer.elapsed() >= alertTimer.interval)
    {
        alert.send();
        alertTimer.start();
        
    }
    delay(5000);
}