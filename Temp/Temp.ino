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

int percentageSettingPin = A0;
int enableSwitchPin = 5;
int forwardSwitchPin = 6;
int reverseSwitchPin = 7;
int sensorValue = 0;
int percent = 0;

int PULLED_DOWN = 0;

directions direction = neutral;
bool enabled = false;

void setup()
{
  pinMode(enableSwitchPin, INPUT_PULLUP);
  pinMode(forwardSwitchPin, INPUT_PULLUP);
  pinMode(reverseSwitchPin, INPUT_PULLUP);
  pinMode(percentageSettingPin, INPUT);

  Serial.begin(115200);

  lcd.begin(16, 2); // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.clear();
}

void loop()
{
  sensorValue = analogRead(percentageSettingPin);
  percent = map(sensorValue, 3, 1020, 0, 100);
  char percentageString[4];
  itoa(percent, percentageString, 10);

  lcd.clear();
  lcd.setCursor(0, 0);
  if (digitalRead(forwardSwitchPin) == PULLED_DOWN)
  {
    direction = forward;
    lcd.write("Forward ");
  }
  else if (digitalRead(reverseSwitchPin) == PULLED_DOWN)
  {
    direction = reverse;
    lcd.write("Reverse ");
  }
  else
  {
    direction = neutral;
    lcd.write("Neutral ");
  }
  lcd.write(percentageString);
  lcd.write("%");

  enabled = digitalRead(enableSwitchPin) == PULLED_DOWN;
  lcd.setCursor(0, 1);
  lcd.write(enabled ? "Enabled         " : "Disabled        ");

  delay(200);
}

bool isPulledDown(int reading)
{
  return reading == PULLED_DOWN;
}
