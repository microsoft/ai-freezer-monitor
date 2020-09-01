#include "AdafruitIO_WiFi.h"

class database
{
    public:
        database(char *name);
        void write(float data);
        void init();
    
    private:
        AdafruitIO_Feed *temperature;
        void run();
   
};