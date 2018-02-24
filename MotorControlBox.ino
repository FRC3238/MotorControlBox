4df
#include <LiquidCrystal.h>; 
#include <Servo.h>;

Servo servo;
LiquidCrystal lcd(12, 11, 6, 5, 3, 2);

int sensorValue;
int percent;
int servoValue;
int state;
int flip;//flip is either -1, 0 or 1. this will be a multiplier for the end output to the jaguar, to "flip" the output to negative, posisitve, or nothing.
int percentShow;

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  lcd.begin(16, 2);
  servo.attach(9);
  state = 0;
  flip = 0;
  pinMode(7, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);//pin 19 on ATMega chip without Arduino Board
  pinMode(10, INPUT_PULLUP);//pin 16 on ATMega chip without Arduino Board
  lcd.setCursor(0,0);
  lcd.print("MotoCont 2.2");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("By Nick Sorensen");
  lcd.setCursor(0,1);
  lcd.print("And Cody Frost");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Also...");
  lcd.setCursor(0,1);
  lcd.print("A. Sorb'jorben");
  delay(3000);
  lcd.clear();
}

// the loop routine runs over and over again forever:
void loop() 
{
  sensorValue = analogRead(A5);
  percent = map(sensorValue, 0, 1023, -100, 100);
  servoValue = map(sensorValue, 0, 1023, 0, 179);
  
  if(flip == 0)
  {
    percentShow = percent;
    percent = percent*flip;
  }
  else
  {
    percent = percent*flip;
    percentShow = percent;
  }
  
  switch(flip)
  {  
    case 0: 
    servoValue = 90;
    break;
    
    case -1:
    servoValue = 180+(servoValue*-1);
    break;
    
    default:
    break;
  }
  
  
  switch (state)
  {
     case 0: //Disabled state
     lcd.setCursor(0,1);
     lcd.print("State: Disabled!");
     lcd.setCursor(0,0);
     lcd.print("Percent: ");
     lcd.print(percentShow);
     lcd.print("      ");
     servo.write(90);
     break;
     
     
     case 1:
     lcd.setCursor(0,1);
     lcd.print("State: Enabled! ");
     lcd.setCursor(0,0);
     lcd.print("Percent: ");
     lcd.print(percentShow);
     lcd.print("      ");
     servo.write(servoValue);
     break;
     
     default:
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Not Sure?");
     servo.write(90);
     break;
   
  }
  
  flip = 0;
  if(digitalRead(13) == 0)
  {
    flip = 1;
  }
  if(digitalRead(10) == 0)
  {
    flip = -1;
  }
  
  if(digitalRead(7) == 1)
  {
    state = 0;
  }
  if(digitalRead(7) == 0)
  {
    state = 1;
  }
  delay(10);        // delay in between reads for stability
}
