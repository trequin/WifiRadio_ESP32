# WifiRadio_ESP32
Firmware programmed on a MakePython by way of a Arduino Communication... It works
New sketch for use with the TTGO ESP32 by Lily Go is under development

To program a MakePython ESP32 with an Arduino Uno, you can use the Arduino IDE to develop the ESP32: 
Install the development board 
Install the library 
Open the Arduino IDE 
Upload an example demo, such as the Basic Core, to see the code synchronized with the device 
Start your own programming projects 
You can also connect your ESP32 to your computer and use Arduino Cloud to add the board, select its type, and name it. This will generate a device ID and secret key. 

Here are some other tips for programming an ESP32: 
The Espressif IoT Development Framework (Espressif ESP IDF) is considered the official and best way to program an ESP32. 
Most developers use the Microsoft VS Code IDE. 
When starting with MicroPython, use the Stable firmware builds. 
If your board has SPIRAM support, you can use the firmware with SPIRAM support to access more RAM for Python objects. 


THe followingcode is inteded for updates as needed by the developer:
String ssid =     "<enter wifi ssid here>";
String password = "<enter password here";

String stations[] ={
        "https://stream.treevine.life/bosshogg",
        "https://stream.treevine.life/noise",
        "https://stream.treevine.life/zonasur"
        }
