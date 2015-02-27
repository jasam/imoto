#include <LiquidCrystal.h>
int count = 0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  Serial.begin(9600);
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  analogWrite(6,15);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  analogWrite(9,28836);
  lcd.print("LCD test!!");
  
}

void loop() 
{
   analogWrite(9,28836);
   lcd.setCursor(0, 0);
   lcd.print("1");
   delay(2000);
}


