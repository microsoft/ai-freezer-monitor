// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
// 
// Class that represents Adafruit IO feed

#include "AdafruitIO_WiFi.h"

class database
{
    public:
        database(char *name);
        void write(float data);
        void init();
    
    private:
        AdafruitIO_Feed *feed;
        void run();
   
};