/*
  Version 3 of DriMEReV code
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int Z3sensorPin = A0;
const int Z4sensorPin = A1;

const int Z3heatSwitch = 9;
const int Z4heatSwitch = 10;

int Z3time = 0;
int Z4time = 0;

const float Z3setTemp = 30.0;
const float Z4setTemp = 26.0;

int Z34extratime;
int Z3extratime;
int Z4extratime;

  float Z3setVal = (Z3setTemp+50)/0.48828;
  float Z4setVal = (Z4setTemp+50)/0.48828;

void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  Serial.begin(9600);

  pinMode(Z3heatSwitch, OUTPUT);
  pinMode(Z4heatSwitch, OUTPUT);
  
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
  lcd.print("Booting...");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Charging");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("capacitors...");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("3:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("4:");

  lcd.setCursor(2, 0);
  lcd.print((0.48828*analogRead(Z3sensorPin))-50);
  lcd.setCursor(2, 1);
  lcd.print((0.48828*analogRead(Z4sensorPin))-50);
  delay(4000);

  // set up the switch pin as an in
}

void loop() {
  // check the status of the switch  

  for (Z34extratime = 0; analogRead(Z3sensorPin) < Z3setVal && analogRead(Z4sensorPin) < Z4setVal && Z34extratime < 8; Z34extratime++) {

    digitalWrite(Z3heatSwitch, HIGH);
    digitalWrite(Z4heatSwitch, HIGH);
    delay(1000);
  }

  for (Z3extratime = 0; analogRead(Z3sensorPin) < Z3setVal && analogRead(Z4sensorPin) > Z4setVal && Z3extratime < 8; Z3extratime++) {

    digitalWrite(Z3heatSwitch, HIGH);
    digitalWrite(Z4heatSwitch, LOW);
    delay(1000);
  }

  for (Z4extratime = 0; analogRead(Z3sensorPin) > Z3setVal && analogRead(Z4sensorPin) < Z4setVal && Z4extratime < 8; Z4extratime++) {

    digitalWrite(Z3heatSwitch, LOW);
    digitalWrite(Z4heatSwitch, HIGH);
    delay(1000);
  }

  digitalWrite(Z3heatSwitch, LOW);
  digitalWrite(Z4heatSwitch, LOW);
  
  Z3time = Z3time + Z34extratime;
  Z4time = Z4time + Z34extratime;
  Z3time = Z3time + Z3extratime;
  Z4time = Z4time + Z4extratime;
  Z34extratime = 0;
  Z3extratime = 0;
  Z4extratime = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("3:");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("4:");
   // set the cursor to column 0, line 0
  lcd.setCursor(2, 0);
  // print some text
  lcd.print((0.48828*analogRead(Z3sensorPin))-50);
  // move the cursor to the second line
  lcd.setCursor(9, 0);
  lcd.print(Z3time);

  // set the cursor to column 0, line 0
  lcd.setCursor(2, 1);
  // print some text
  lcd.print((0.48828*analogRead(Z4sensorPin))-50);
  // move the cursor to the second line
  lcd.setCursor(9, 1);
  lcd.print(Z4time);

 
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
