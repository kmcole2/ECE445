#include "PWM.h"
#include <Wire.h>
#include "rgb_lcd.h"

#define irsensor A0
unsigned int ir_value;

rgb_lcd lcd;

void setup() {
  //LCD Initialization
  lcd.begin(16, 2);               // set up the LCD's number of columns and rows:
  lcd.print("Dispensing:Sugar");  // Print a message to the LCD.
  lcd.setCursor(0, 1);            // Move cursor to second line
  lcd.print("Dispensing:Sugar");  // Print on second line
  lcd.display();
  pinMode(irsensor, INPUT); //declare pin A0 as input

}

void loop() {
  // put your main code here, to run repeatedly:
  float sample1 = 0;
  ir_value = analogRead(irsensor);      //take reading from sensor

  for (int i = 1; i < 10; i++)
  {
    sample1 = analogRead(irsensor);
    ir_value = ir_value + sample1;
    delay(1);
  }
  ir_value = ir_value / 10;

  lcd.clear();
  lcd.print(ir_value);
  delay(500);
}
