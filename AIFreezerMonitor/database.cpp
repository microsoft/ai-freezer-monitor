// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// Class that represents Adafruit IO feed

#include "database.h"
#include "config.h"

database::database(char *name)
{
    feed = io.feed(name);
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
        feed->save(data);
        if (Serial)
        {     
            Serial.print("Sending: ");
            Serial.print(data);
            Serial.println();
        }
    }
