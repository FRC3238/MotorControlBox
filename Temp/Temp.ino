// #include <Wire.h> // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include "LiquidCrystal_I2C.h"

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

void setup()
{
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.print("123");

  lcd.begin(16, 2); // initialize the lcd for 16 chars 2 lines, turn on backlight

  lcd.clear();
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.write("Bubba Suds");
  lcd.setCursor(0, 1); //Start at character 0 on line 0
  lcd.write("3238    3238");
  delay(500);
}

void loop()
{
  delay(400);
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Top Row         ");
  lcd.setCursor(0, 1);
  lcd.write("Bottom Row      ");
  // delay(100);

  if (digitalRead(8) == 0)
  {
    Serial.println("forward");
  }
  else if (digitalRead(9) == 0)
  {
    Serial.println("backward");
  }
  else
  {
    Serial.println("neutral");
  }
  delay (1);
}
