# Auto Air Filtration

## What is it?
It's an Arduino connected to a dust sensor that turns on a relay when the sensor detects PM2.5 particles higher than a set threshold. The relay should be hooked up to some sort of Aircleaner.

 ![Project Collage](auto-aircleaner.jpg)

## Parts needed?
- [Arduino Nano](https://amzn.to/30k7ogw) (Could probably use any Arduino.)
- [Dust Sensor](https://amzn.to/3h12ESO) 
  - I ended up using a [breakout board](https://amzn.to/30plehA) for the Dust Sensor.. you can choose to cut and solder directly to the wires.
- [Solid State Relay](https://amzn.to/3cNMJnw)
- [OLED Screen](https://amzn.to/3hewW4T)
- [Prototype Board](https://amzn.to/2XJdDbP)
- [15 Amp - 120v Recepticle](https://amzn.to/3h55t5j)
- [4 inch box](https://amzn.to/2BNHh7t)
- Sacrificial Power plug or [Plug Tail](https://amzn.to/2MFUl0L)

## How does it work?
This is a fairly basic Arduino project. We monitor the readings from the dust sensor and when it goes over a certain limit, we push power to the relay, which in turn, activates the fan. 

## Basic How to
- Connecting the Dust sensor
  - Connect Arduino 5v output to VCC pin on Dust Sensor
  - Connect Arduino GND to GND pin on Dust Sensor
  - Connect Arduino Digital Pin 2 to TX pin on Dust Sensor
- Connecting the OLED
  - Connect Arduino 5v output to VCC on OLED
  - Connect Arduino GND to GND on OLED
  - Connect Arduino Analog Pin 4 to SDA on OLED
  - Connect Arduino Analog Pin 5 to SCL on OLED
- Connecting the Relay
  - Connect Arduino GND to Negative on the input side on the Relay (3-32VDC side)
  - Connect Arduino Digital Pin 4 to the Positive on the input side on the Relay (3-32VDC)
### DANGER HIGH VOLTAGE DON'T MESS THIS UP... YOU COULD ELECTROCUTE YOURSELF.
- Wire up outlet to the relay on the positive side... just as you would a switch
  - Ground coming in from the wall to the Green post on outlet
  - White coming in from the wall to the silver post on outlet
  - Black coming in from the wall, to the relay, then to brass post on outlet.

### Arduino  
- Add the following libraries to your Arduino IDE:
  - Adafruit SSD1306 (for oled)
  - Adafruit GFX Library (for oled)
  - PMS Library (For Dust sensor)
- Grab the code from the .ino file and push it to your Arduino... it should warm up for 4 seconds then display your PM numbers. There are 2 settings you can play with in the file... Threshold and Fan Timeout... set those to numbers you find reasonable. 


## Disclaimer
Not my fault if you burn your house down... or get wood dust inhalation or anything else... Be safe and follow safe handling directions. 

Also links above are Amazon Affiliate links... I'll get a small percentage of the purchase price... no affect to your bottom line. 