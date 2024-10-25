/*
* Name: clock and temp project
* Author: Katarina Penava
* Date: 2024-10-11
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* It also measures temperature with an analog temperature module and triggers an alarm using LEDs 
* when the temperature exceeds a user-defined threshold set by a potentiometer.
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"


// Init constants
const int potPin = A0;
const int tmpPin = A1;

// Init global variables

//övrigt/vet ej för tillfället

// construct objects
RTC_DS3231 rtc;                                 //?
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC


void setup() {
  // init communication
  //Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_7x13);

  pinMode(potPin, INPUT);  // potentiometern
  pinMode(tmpPin, INPUT);  // temperatur mätaren
  Serial.begin(9600);
  for (int i = 10; i <= 13; i++) {  // digital pin för lamporna
    pinMode(i, OUTPUT);
  }

  // Init Hardware
}

void loop() {
  //oledWrite("TIME: " + getTime(), "TEMP: " + String(getTemp(), "THRES:" + String(getThreshold()));
  oledWrite("TIME: " + getTime(),
            "TEMP: " + String(getTemp()),
            "THRES: " + String(getThreshold()));


  //Serial.println(getThreshold());  // treshold med potentiometern
  //Serial.println(getTemp());       // temperatur

  if (getTemp() > getThreshold()) {
    alarm();
  }


  delay(100);
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {

  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  //steinhart-hart coeficients for thermistor

  Vo = analogRead(tmpPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String text1, String text2, String text3) {
  u8g.firstPage();
  do {
    u8g.drawStr(0, 20, text1.c_str());
    u8g.drawStr(0, 40, text2.c_str());
    u8g.drawStr(0, 60, text3.c_str());
  } while (u8g.nextPage());
}


int getThreshold() {  // treshold
  return map(analogRead(potPin), 0, 1023, 20, 40);
}


void alarm() {  // funktionen för lamporna
  for (int i = 10; i <= 13; i++) {
    digitalWrite(i, HIGH);
    delay(50);
    digitalWrite(i, LOW);
  }
}
