#include "database.h"
#include "config.h"

database::database(char *name)
{
    temperature = io.feed(name);
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