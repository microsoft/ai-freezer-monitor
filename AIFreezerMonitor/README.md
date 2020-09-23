# AI Freezer Monitor

With your model trained and exported to a C array you're ready to implement it on your Feather Huzzah 32. We'll need to update the software on our ESP32, but the hardware can stay the same. In fact, it is best to leave the thermocouple in the freezer since moving it may affect the results of the machine learning model.

## Code

Clone this repo to your computer, or you can download the directory for this project [here](https://github.com/microsoft/freezer-temp-monitor/archive/main.zip)

Once you have downloaded the project files, you'll need to create a config.h file and fill in your AdafruitIO and WiFi credentials.

1. In the *AIFreezerMonitor* folder create a new text file called *config.h*
    > Note: You can also copy the config.h file you created for the data collection code.

1. Copy and paste the code below into that that file and save:
    ```C++
    /************************ Adafruit IO Config *******************************/

    // visit io.adafruit.com if you need to create an account,
    // or if you need your Adafruit IO key.
    #define IO_USERNAME "your-username"
    #define IO_KEY "your-key"

    /******************************* WIFI **************************************/

    #define WIFI_SSID "your-ssid"
    #define WIFI_PASS "your-password"

    #include "AdafruitIO_WiFi.h"

    AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
    ```

1. Find your Adafruit IO credentials in the top right corner of the Adafruit IO webpage. 
    ![Adafruit IO Webpage](/media/iokeys.png)

1. Copy and paste them in here between the quotes:
    ```C++
    #define IO_USERNAME "your_username"
    #define IO_KEY "your_key"
    ```
    >*Remember to treat your key like a password*
1. Next you will need to add the WiFi SSID, or network name, and the password. Note: The code doesn't support WiFi networks that use a captive portal.
    ```C++
    #define WIFI_SSID "your_ssid"
    #define WIFI_PASS "your_pass"
    ```
1. Move the model_data.h file you created earlier in to the *AIFreezerMonitor* directory

## Flashing your board

1. Follow the first section of this [guide](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) to add the ESP32 extension to the Arduino IDE.

1. Install the libraries listed below using Arduino's Library manager. If you have used the library manager before [here](https://www.arduino.cc/en/guide/libraries) is a helpful guide.
    1. Adafruit IO Arduino
    1. Adafruit MCP9600
    1. TensorFlowLite_ESP32
    > Note: If you're prompted to install other dependencies for these libraries, select *Install All*

1. With FreezerTempAlert.ino open in the Arduino IDE select **Tools>Board>Adafruit ESP32 Feather**

1. Select the active COM Port in **Tools>Port**

1. Press the *Upload* button   
    ![Arduino upload button](/media/upload.png)

## Installing

If you moved the thermocouple in order to upload the new code, do your best to place back in the same place in the freezer. If the thermocouple is moved too far away from the training position it may misidentify normal operation as an anomaly.

Your IFTTT warning should still be working the same as before, so you don't need to change anything there.
