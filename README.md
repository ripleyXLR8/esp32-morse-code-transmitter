# ESP-32 Morse Code Transmiter

## What's the point?

This is a very simple software which translate a string into morse code. The resulting code can be transmited by blinking leds and/or sending web requests corresponding to DASHES and DOTS. To facilitate decoding, blinking and/or web-requests can use different pins and URLs for odd and even characters. You can also customize every aspect of the morse code (speed, pause, duration of dashes and dots) and add a pause and a start signal at the beginning.

## How to use it?

1) Add HTTPClient.h and WiFi.h library to your arduino IDE and open the *.ino file. 

2) Set the following variables at the beginning of the code :

- Set "ssid" and "password" variables to allow your ESP32 to connect to your wifi network.

- Replace the "stringToTransmit" variable by the string you want to transmit.

- "ledPinEven", "ledPinOdd" and "ledPinStartSignal" variables allow you to define the pins of your ESP-32 connected to the blinkind led. (if you don't use the alternate blinking feature and the start signal feature, you just need to define the "ledPinEven" variable).

- In the section "SOFTWARE CONFIGURATION" you can configure which function will be enabled. (Blinking, WebRequest, Led Start Signal, Alternate Blinking on odd and even characteres).

- In the section "MORSE TIMING CONFIGURATION" you can configure how fast the morse code is transmitted.

Have fun and HPBD Clémence.
 
