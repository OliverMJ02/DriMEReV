/*
  Version 3 of DriMEReV code
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int Z1sensorPin = A0;
const int Z2sensorPin = A1;

const int Z1heatSwitch = 9;
const int Z2heatSwitch = 10;

int Z1time = 0;
int Z2time = 0;

const float Z1setTemp = 23.0;
const float Z2setTemp = 28.0;

int Z12extratime;
int Z1extratime;
int Z2extratime;

  float Z1setVal = (Z1setTemp+50)/0.48828;
  float Z2setVal = (Z2setTemp+50)/0.48828;

void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  Serial.begin(9600);

  pinMode(Z1heatSwitch, OUTPUT);
  pinMode(Z2heatSwitch, OUTPUT);
  
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("DriMEReV by");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("PEW-Technologies");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Starting up...");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Priming");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("sensors...");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("1:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("2:");

  lcd.setCursor(2, 0);
  lcd.print((0.48828*analogRead(Z1sensorPin))-50);
  lcd.setCursor(2, 1);
  lcd.print((0.48828*analogRead(Z2sensorPin))-50);
  delay(4000);
}

void loop() {
  // check the status of the switch  

  for (Z12extratime = 0; analogRead(Z1sensorPin) < Z1setVal && analogRead(Z2sensorPin) < Z2setVal && Z12extratime < 8; Z12extratime++) {

    digitalWrite(Z1heatSwitch, HIGH);
    digitalWrite(Z2heatSwitch, HIGH);
    delay(1000);
  }

  for (Z1extratime = 0; analogRead(Z1sensorPin) < Z1setVal && analogRead(Z2sensorPin) > Z2setVal && Z1extratime < 8; Z1extratime++) {

    digitalWrite(Z1heatSwitch, HIGH);
    digitalWrite(Z2heatSwitch, LOW);
    delay(1000);
  }

  for (Z2extratime = 0; analogRead(Z1sensorPin) > Z1setVal && analogRead(Z2sensorPin) < Z2setVal && Z2extratime < 8; Z2extratime++) {

    digitalWrite(Z1heatSwitch, LOW);
    digitalWrite(Z2heatSwitch, HIGH);
    delay(1000);
  }

  digitalWrite(Z1heatSwitch, LOW);
  digitalWrite(Z2heatSwitch, LOW);
  
  Z1time = Z1time + Z12extratime;
  Z2time = Z2time + Z12extratime;
  Z1time = Z1time + Z1extratime;
  Z2time = Z2time + Z2extratime;
  Z12extratime = 0;
  Z1extratime = 0;
  Z2extratime = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
    // Print a message to the LCD.
  lcd.print("1:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("2:");
   // set the cursor to column 0, line 0
  lcd.setCursor(2, 0);
  // print some text
  lcd.print((0.48828*analogRead(Z1sensorPin))-50);
  // move the cursor to the second line
  lcd.setCursor(9, 0);
  lcd.print(Z1time);


  // set the cursor to column 0, line 0
  lcd.setCursor(2, 1);
  // print some text
  lcd.print((0.48828*analogRead(Z2sensorPin))-50);
  // move the cursor to the second line
  lcd.setCursor(9, 1);
  lcd.print(Z2time);

 
}
/*
  Version 1 of DriMEReVOL code


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int Z1sensorPin = A0;
const int Z2sensorPin = A1;

const int Z1heatSwitch = 9;
const int Z2heatSwitch = 10;

int Z1time = 0;
int Z2time = 0;

const float Z1setTemp = 30.0;
const float Z2setTemp = 26.0;


void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  Serial.begin(9600);

  pinMode(Z1heatSwitch, OUTPUT);
  pinMode(Z2heatSwitch, OUTPUT);
  
  float Z1setVal = (Z1setTemp+50)/0.48828;
  float Z2setVal = (Z2setTemp+50)/0.48828;

  // set up the switch pin as an input


  // Print a message to the LCD.
  lcd.print("1:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("2:");
}

void loop() {
  // check the status of the switch



  int Z1sensorVal = analogRead(Z1sensorPin);
  Serial.print("Zone 1 Sensor Value: ");
  Serial.print(Z1sensorVal);

  float Z1voltage = (Z1sensorVal / 1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(Z1voltage);

  float Z1temperature = (Z1voltage - 0.5) * 100;
  Serial.print(", degrees C: ");
  Serial.print(Z1temperature);


  int Z2sensorVal = analogRead(Z2sensorPin);
  Serial.print("Zone 2 Sensor Value: ");
  Serial.print(Z2sensorVal);

  float Z2voltage = (Z2sensorVal / 1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(Z2voltage);

  float Z2temperature = (Z2voltage - 0.5) * 100;
  Serial.print(", degrees C: ");
  Serial.print(Z2temperature);

 // set the cursor to column 0, line 0
  lcd.setCursor(2, 0);
  // print some text
  lcd.print(Z1temperature);
  // move the cursor to the second line
  lcd.setCursor(9, 0);
  lcd.print(Z1time);


  // set the cursor to column 0, line 0
  lcd.setCursor(2, 1);
  // print some text
  lcd.print(Z2temperature);
  // move the cursor to the second line
  lcd.setCursor(9, 1);
  lcd.print(Z2time);
  

  if (Z1temperature < Z1setTemp && Z2temperature < Z2setTemp) {

    digitalWrite(Z1heatSwitch, HIGH);
    digitalWrite(Z2heatSwitch, HIGH);
    Z1time = Z1time + 1;
    Z2time = Z2time + 1;
    delay(1000);
  }

if (Z1temperature < Z1setTemp && Z2temperature > Z2setTemp) {

    digitalWrite(Z1heatSwitch, HIGH);
    digitalWrite(Z2heatSwitch, LOW);
    Z1time = Z1time + 1;
    delay(1000);
  }

if (Z1temperature > Z1setTemp && Z2temperature < Z2setTemp) {

    digitalWrite(Z2heatSwitch, HIGH);
    digitalWrite(Z1heatSwitch, LOW);
    Z2time = Z2time + 1;
    delay(1000);
  }

  else {

    digitalWrite(Z1heatSwitch, LOW);
    digitalWrite(Z2heatSwitch, LOW);
  }

 
}*/
