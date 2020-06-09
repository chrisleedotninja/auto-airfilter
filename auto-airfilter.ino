#include "PMS.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

SoftwareSerial Serial1(2, 3); // RX, TX
 
PMS pms(Serial1);
PMS::DATA data;

// Settings you can configure
//***************************************************************************
// How long to run the fan after coming under threshold (default=15min)
long fan_timeout = 900000; 
// Threshold for pm2.5 particles
int pm2_5max = 27; 
//***************************************************************************

int fanPowerPin = 4;  // Digital Pin that the Relay is connected to
long start_millis;
int fanPowerStatus = LOW; //Set fan off when starting


void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  
  if(!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  pinMode(fanPowerPin, OUTPUT);
  digitalWrite(fanPowerPin, LOW);
  lcd.clearDisplay();
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(0, 10);
  lcd.println("Warming Up!");
  lcd.display();
  delay(4000);
}
 
void loop()
{
  long fan_time_left = 0;
  if (pms.read(data))
  {
    if (data.PM_AE_UG_2_5 > pm2_5max) 
    {
      start_millis = millis();
      fanPowerStatus = HIGH;
      fan_time_left = fan_timeout;
      digitalWrite(fanPowerPin, fanPowerStatus);
    } else if ((millis() - start_millis < fan_timeout) && (fanPowerStatus == HIGH))
    {
       fan_time_left = fan_timeout - (millis() - start_millis);
    } else if ((millis() - start_millis > fan_timeout) && (data.PM_AE_UG_2_5 <= pm2_5max) && (fanPowerStatus == HIGH))
    {
      fanPowerStatus = LOW;
      digitalWrite(fanPowerPin, fanPowerStatus);
      fan_time_left = 0;
    } 
    print_screen (data, fan_time_left);
    delay(1000);
  }
}

void print_screen (PMS::DATA data, long time_left)
{
  int tseconds = time_left / 1000;
  int tminutes = tseconds / 60;
  int seconds = tseconds % 60;
  lcd.clearDisplay();
  lcd.setTextSize(1);
  lcd.setCursor(0, 10);
  lcd.println("Dust Concentration");
  lcd.print("PM1.0: "); lcd.println(data.PM_AE_UG_1_0);
  lcd.print("PM2.5: "); lcd.println(data.PM_AE_UG_2_5);
  lcd.print("PM10 : "); lcd.println(data.PM_AE_UG_10_0);
  lcd.println("");
  lcd.print("Time Left: "); lcd.print(tminutes); lcd.print("m | "); lcd.print(seconds); lcd.println("s");
  lcd.display();
}
