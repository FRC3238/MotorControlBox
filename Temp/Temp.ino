#include <String.h>
// #include <Wire.h> // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

enum directions
{
  forward,
  neutral,
  reverse
};

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

int enableSwitchPosition = 5;
int forwardSwitchPosition = 6;
int reverseSwitchPosition = 7;

int PULLED_DOWN = 0;

directions direction = neutral;
bool enabled = false;

void setup()
{
  pinMode(enableSwitchPosition, INPUT_PULLUP);
  pinMode(forwardSwitchPosition, INPUT_PULLUP);
  pinMode(reverseSwitchPosition, INPUT_PULLUP);

  Serial.begin(115200);

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
  if (digitalRead(forwardSwitchPosition) == PULLED_DOWN)
  {
    direction = forward;
    lcd.setCursor(0, 0);
    lcd.write("Forward        ");
  }
  else if (digitalRead(reverseSwitchPosition) == PULLED_DOWN)
  {
    direction = reverse;
    lcd.setCursor(0, 0);
    lcd.write("Reverse         ");
  }
  else
  {
    direction = neutral;
    lcd.setCursor(0, 0);
    lcd.write("Neutral         ");
  }

  enabled = digitalRead(enableSwitchPosition) == PULLED_DOWN;
  if (enabled)
  {
    lcd.setCursor(0, 1);
    lcd.write("Enabled         ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.write("Disabled        ");
  }

  delay(1);
}

// int writeToLCD(char* message, int row)
// {
//   lcd.setCursor(0, 0);
//   lcd.write(message);
// }

bool isPulledDown(int reading)
{
  return reading == PULLED_DOWN;
}
