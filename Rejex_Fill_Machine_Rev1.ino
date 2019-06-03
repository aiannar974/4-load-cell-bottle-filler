#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);

double m_1;
double b_1;
double y0_1;
double y1_1;
double x0_1;
double x1_1;
double m_2;
double b_2;
double y0_2;
double y1_2;
double x0_2;
double x1_2;
double m_3;
double b_3;
double y0_3;
double y1_3;
double x0_3;
double x1_3;
double m_4;
double b_4;
double y0_4;
double y1_4;
double x0_4;
double x1_4;
const byte DOUT1 = 2;
const byte CLK1 = 1;
const byte DOUT2 = 4;
const byte CLK2 = 3;
const byte DOUT3 = 6;
const byte CLK3 = 5;
const byte DOUT4 = 8;
const byte CLK4 = 7;
const byte FillPin1 = 9;
const byte FillPin2 = 10;
const byte FillPin3 = 11;
const byte FillPin4 = 12;
const byte YesPin = 13;
const byte ValvePin1 = A1;
const byte ValvePin2 = A2;
const byte ValvePin3 = A3;
const byte ValvePin4 = A6;
const byte PotPin = A7;
const byte NoPin = 0;
int FillButton1 = 0;         // variable for reading the pushbutton status
int FillButton2 = 0;
int FillButton3 = 0;
int FillButton4 = 0;
  //  int FillState1 = 0;
  //  int FillState2 = 0;
  //  int FillState3 = 0;
  //  int FillState4 = 0;
//  int ValvePin1 = 0;
//  int ValvePin2 = 0;
//  int ValvePin3 = 0;
//  int ValvePin4 = 0;
  double fillwtlimit = 0;
  double potval = 0;
  double CurrentBottleWt1 = 0;
  double CurrentBottleWt2 = 0;
  double CurrentBottleWt3 = 0;
  double CurrentBottleWt4 = 0;
  double NewBottleWtAve1 = 0;
  double NewBottleWtAve2 = 0;
  double NewBottleWtAve3 = 0;
  double NewBottleWtAve4 = 0;
  double PrevBottleWtAve1 = 0;
  double PrevBottleWtAve2 = 0;
  double PrevBottleWtAve3 = 0;
  double PrevBottleWtAve4 = 0;
  int FillStartFlag1 = 0;
  int FillStartFlag2 = 0;
  int FillStartFlag3 = 0;
  int FillStartFlag4 = 0;
  int NoPinRead = 0;
  int YesPinRead = 0;
  int Yes_No = 0;
  long Temp = 0;

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;


void setup() {

  lcd.begin();//Initializing display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light

  Serial.begin(9600);
  //Reading Calibration Factor from EEPROM

  // initialize the pins as an input or output:
  pinMode(FillPin1, INPUT);
  pinMode(FillPin2, INPUT);
  pinMode(FillPin3, INPUT);
  pinMode(FillPin4, INPUT);
  pinMode(NoPin, INPUT);
  pinMode(YesPin, INPUT);
  pinMode(ValvePin1, OUTPUT);
  pinMode(ValvePin2, OUTPUT);
  pinMode(ValvePin3, OUTPUT);
  pinMode(ValvePin4, OUTPUT);
  pinMode(PotPin, INPUT); // wire potentiometer center post to A7 analog in

  scale1.begin(DOUT1, CLK1);
  //scale1.set_scale(calibration_factor1); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale2.begin(DOUT2, CLK2);
  //scale2.set_scale(calibration_factor2); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale3.begin(DOUT3, CLK3);
  //scale3.set_scale(calibration_factor3); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale4.begin(DOUT4, CLK4);

  delay(5000);

    y0_1=0.0;
    y0_2=0.0;
    y0_3=0.0;
    y0_4=0.0;
    y1_1=0.314;
    y1_2=y1_1;
    y1_3=y1_1;
    y1_4=y1_1;
    

  // Calibration Routine
  lcd.clear();//Clean the screen
  lcd.setCursor(0,0); 
  lcd.print("Calibrate");
  delay(3000);
  
  YesPinRead = 0;
  NoPinRead = 0;

    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("Empty Scales");
    lcd.setCursor(0,1); 
    lcd.print("Press Y");
  
    while (YesPinRead=0) {
    YesPinRead=digitalRead(YesPin);
    Serial.print("Remove all weights from scale and press 'Yes' button");
    }

    delay(2000);
    x0_1=scale1.get_units(10);
    x0_2=scale2.get_units(10);
    x0_3=scale3.get_units(10);
    x0_4=scale4.get_units(10);

    lcd.clear();//Clean the screen
    lcd.setCursor(0,0);    
    lcd.print("Add Cal Weight");
    lcd.setCursor(0,1);
    lcd.print("Scale1 Press Y");
    while (YesPinRead=0) {
      YesPinRead=digitalRead(YesPin);
    }
    delay(2000);
    x1_1 = scale1.get_units(10);
    m_1=(y1_1-y0_1)/(x1_1-x0_1);
    b_1=((y0_1*x1_1)-(y1_1*x0_1))/(x1_1-x0_1);

    lcd.clear();//Clean the screen
    lcd.setCursor(0,0);    
    lcd.print("Add Cal Weight");
    lcd.setCursor(0,1);
    lcd.print("Scale2 Press Y");
    while (YesPinRead=0) {
      YesPinRead=digitalRead(YesPin);
    }
    delay(2000);
    x1_2 = scale2.get_units(10);
    m_2=(y1_2-y0_2)/(x1_2-x0_2);
    b_2=((y0_2*x1_2)-(y1_2*x0_2))/(x1_2-x0_2);    

    lcd.clear();//Clean the screen
    lcd.setCursor(0,0);    
    lcd.print("Add Cal Weight");
    lcd.setCursor(0,1);
    lcd.print("Scale3 Press Y");
    while (YesPinRead=0) {
      YesPinRead=digitalRead(YesPin);
    }
    delay(2000);
    x1_3 = scale3.get_units(10);
    m_3=(y1_3-y0_3)/(x1_3-x0_3);
    b_3=((y0_3*x1_3)-(y1_3*x0_3))/(x1_3-x0_3);

    lcd.clear();//Clean the screen
    lcd.setCursor(0,0);    
    lcd.print("Add Cal Weight");
    lcd.setCursor(0,1);
    lcd.print("Scale4 Press Y");
    while (YesPinRead=0) {
      YesPinRead=digitalRead(YesPin);
    }
    delay(2000);
    x1_4 = scale4.get_units(10);
    m_4=(y1_4-y0_4)/(x1_4-x0_4);
    b_4=((y0_4*x1_4)-(y1_4*x0_4))/(x1_4-x0_4);  

  lcd.clear();//Clean the screen
  lcd.setCursor(0,0);    
  lcd.print("Machine Ready");
  lcd.setCursor(0,1);
  lcd.print("");
  delay(2000);

  PrevBottleWtAve1 = 0.0;
  PrevBottleWtAve2 = 0.0;
  PrevBottleWtAve3 = 0.0;
  PrevBottleWtAve4 = 0.0;

}

void loop() {

  // read the input on analog PotPin from potentiometer for fillwt calc:
  int potval = analogRead(PotPin);
  // potval ranges 0 to 1023 and convert to ounces range 0 to 1000 grams;
  float fillwtlimit = potval * (1000.0 / 1023.0);
  lcd.clear();//Clean the screen
  lcd.setCursor(0,0);    
  lcd.print("Fill Weight");
  lcd.setCursor(0,1);
  lcd.print(fillwtlimit);

  // read fill buttons;
  FillButton1 = digitalRead(FillPin1);
  FillButton2 = digitalRead(FillPin2);
  FillButton3 = digitalRead(FillPin3);
  FillButton4 = digitalRead(FillPin4);
  
  if (FillStartFlag1 = 1) {
    FillStartFlag1 = FillStartFlag1;
  }
  else {
    FillStartFlag1 = FillButton1;
  }
  
  if (FillStartFlag2 = 1) {
    FillStartFlag2 = FillStartFlag2;
  }
  else {
    FillStartFlag2 = FillButton2;
  }

  if (FillStartFlag3 = 1) {
    FillStartFlag3 = FillStartFlag3;
  }
  else {
    FillStartFlag3 = FillButton3;
  }

  if (FillStartFlag4 = 1) {
    FillStartFlag4 = FillStartFlag4;
  }
  else {
    FillStartFlag4 = FillButton4;
  }

  // read load cells
  double CurrentBottleWt1 = scale1.get_units(1); //scale.get_units() returns a float
  double CurrentBottleWt2 = scale2.get_units(1); //scale.get_units() returns a float
  double CurrentBottleWt3 = scale3.get_units(1); //scale.get_units() returns a float
  double CurrentBottleWt4 = scale4.get_units(1); //scale.get_units() returns a float
  double NewBottleWtAve1 = (0.9 * PrevBottleWtAve1)+(0.1 * CurrentBottleWt1);
  double NewBottleWtAve2 = (0.9 * PrevBottleWtAve2)+(0.1 * CurrentBottleWt2);
  double NewBottleWtAve3 = (0.9 * PrevBottleWtAve3)+(0.1 * CurrentBottleWt3);
  double NewBottleWtAve4 = (0.9 * PrevBottleWtAve4)+(0.1 * CurrentBottleWt4);

  // open and close values
  if ((FillStartFlag1 = 1) && (NewBottleWtAve1 <= fillwtlimit)) {
    digitalWrite(ValvePin1, HIGH);
  }
  else {
    digitalWrite(ValvePin1, LOW);
    FillStartFlag1 = 0;
  }
  if ((FillStartFlag2 = 1) && (NewBottleWtAve2 <= fillwtlimit)) {
    digitalWrite(ValvePin2, HIGH);
  }
  else {
    digitalWrite(ValvePin2, LOW);
    FillStartFlag2 = 0;
  }
  if ((FillStartFlag3 = 1) && (NewBottleWtAve3 <= fillwtlimit)) {
    digitalWrite(ValvePin3, HIGH);
  }
  else {
    digitalWrite(ValvePin3, LOW);
    FillStartFlag3 = 0;
  }
  if ((FillStartFlag4 = 1) && (NewBottleWtAve4 <= fillwtlimit)) {
    digitalWrite(ValvePin4, HIGH);
  }
  else {
    digitalWrite(ValvePin4, LOW);
    FillStartFlag4 = 0;
  }

}
