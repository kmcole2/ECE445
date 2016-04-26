/*
 * 
 * LCD-Arduino Connections 
 * Analog Pin 4 (A4 to SDA) ATMega328 PIN 28
 * Analog Pin 5 (A5 to SCI) ATMega328 PIN 27
 * 
 * GM-Arduino Connections
 * Analog Pin 10, ATMega PIN 17
 * Analog Pin 11, ATMega PIN 16
 * 
 * RLY-Arduino Connections
 * Analog Pin 6, ATMega PIN 12
 * Analog Pin 5, ATMega PIN 11
 * 
   http://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight
   frequency 
   https://code.google.com/archive/p/arduino-pwm-frequency-library/downloads
*/

#include "PWM.h"
#include <Wire.h>
#include "rgb_lcd.h"

#define reading A0
unsigned int ir_value;

/*PWM signal*/
int GMC1_PWM = 11;  //PIN 17 on ATMega
int GMC2_PWM = 10;  //PIN 16

int RLY1 = 6; // PIN 12   
int RLY2 = 5; // PIN 11

rgb_lcd lcd;

void setup() {
  //LCD Initialization
    lcd.begin(16, 2);               // set up the LCD's number of columns and rows:
    lcd.print("Dispensing:Sugar");  // Print a message to the LCD.
    lcd.setCursor(0,1);             // Move cursor to second line
    lcd.print("Dispensing:Sugar");  // Print on second line

    pinMode(GMC1_PWM, OUTPUT);
    pinMode(GMC2_PWM, OUTPUT);
    pinMode(RLY1, OUTPUT);
    pinMode(RLY2, OUTPUT);
    lcd.display();
    digitalWrite(RLY1, LOW);
    digitalWrite(RLY2, LOW);  

}

void loop() {
//
  
  digitalWrite(GMC1_PWM, HIGH);
  digitalWrite(GMC2_PWM, HIGH);
  delayMicroseconds(500); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(GMC1_PWM, LOW);
  digitalWrite(GMC2_PWM, LOW);
  delayMicroseconds(1000 - 500);

}
