/////////////////////////////////////////////////////////////////////////////////////////////
// Below are the integers for the motors for the lift
//int ENABLE = 37;
//int M0 = 38;
//int M1 = 39;
//int M2 = 40;
int RESET = 40;
int SLEEP = 42;
int STEP = 5;
int DIR = 44;
//int FAULT = 44;
///////////////////////////////////////////////////////////////////////////////////////////////
// Below are the integers for the shooter
//int EN = 26;
int M1IN1 = 8;
int M1IN2 = 9;
//int M1FB = A0;
int EncoderA1 = A1;
int EncoderB1 = A2;
//int INV = 28;
//int M1SF = A3;
int M1D1 = 26;
int M1D2 = 24;

//int SLEW = 27;

int M2D1 = 30;
int M2D2 = 28;
//int M2SF = 31;
//int M2FB = 32;
int EncoderA2 = A4;
int EncoderB2 = A5;
int M2IN1 = 10;
int M2IN2 = 11;
//////////////////////////////////////////////////////////////////////////////////////////////////
// Below are the integers for the piston
int EN7 = 7;
int EXTEND = 13;
int RETRACT = 12;
//////////////////////////////////////////////////////////////////////////////////////////////////
int incomingByte = 0;
int shootByte = 0;
bool launch = true;

void setup() {
  // put your setup code here, to run once:
  //////////////////////////////////////////////////////////////////////////////////////
  // Below is the set up for the lift
//  pinMode(ENABLE,OUTPUT); 
//  pinMode(M0,OUTPUT);
//  pinMode(M1,OUTPUT);
//  pinMode(M2,OUTPUT);
  pinMode(RESET,OUTPUT);
  pinMode(SLEEP,OUTPUT);
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
  //pinMode(FAULT,OUTPUT);
  ////////////////////////////////////////////////////////////////////////////////////
  // Below is the set up for the shooter
  pinMode(M1IN1,OUTPUT); // PWM for M1IN1 to move forward
  pinMode(M1IN2,OUTPUT); // PWM for M1IN2 to move backwards
  //pinMode(M1FB,INPUT); // Analog read for M1FB of H-Bridge
  pinMode(EncoderA1,INPUT); // Analog read for Encoder A output on motor 1
  pinMode(EncoderB1,INPUT); // Analog read for Encoder B output on motor 1
  //pinMode(EN,OUTPUT); // Digital input for EN to enable motor driver
  //pinMode(INV,OUTPUT); // Digital input for INV to inverse outputs of M1IN's
  //pinMode(M1SF,INPUT); // Analog input for M1SF
  pinMode(M1D1,OUTPUT); // Digital input for M1D1
  pinMode(M1D2,OUTPUT); // Digital input for M1D2
  //pinMode(SLEW,OUTPUT); // Digital input for SLEW
  pinMode(M2IN1,OUTPUT); // PWM for M2IN1 to move forward
  pinMode(M2IN2,OUTPUT); // PWM for M2IN2 to move backwards
  //pinMode(M2FB,INPUT); // Analog read for M2FB of H-Bridge
  pinMode(EncoderA2,INPUT); // Analog read for Encoder A output on motor 2
  pinMode(EncoderB2,INPUT); // Analog read for Encoder B out[ut on motor 2
  pinMode(M2D1,OUTPUT); // Digital input for M2D1
  pinMode(M2D2,OUTPUT); // Digital input for M2D2
  //pinMode(M2SF,INPUT); // Analog input for M2SF
  ////////////////////////////////////////////////////////////////////////////////////
  // Below is the set up for the piston
  pinMode(EN7,OUTPUT);  //  Digital input for EN7 to enable piston actuation
  pinMode(EXTEND,OUTPUT);  //  Digital input to extend piston
  pinMode(RETRACT,OUTPUT);  //  Digital input to retract piston
  ////////////////////////////////////////////////////////////////////////////////////
  // Below is the set up for serial communication
  Serial.begin(57600);
  Serial.setTimeout(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    
    if (incomingByte == 'g') {
      go_up();
    }
    if (incomingByte == 'h') {
      go_down();
    }
    if (incomingByte == 'x') {
      halt_lift();
    }
    if (incomingByte == 'w') {
      piston_extend();
    }
    if (incomingByte == 'v') {
      piston_retract();
    }
    if (incomingByte == 'u') {
      halt_piston();
    }
    if (incomingByte == 'i') {
      shoot();
    }
    if (incomingByte == 'y') {
      halt_shoot();
    }
      
  }   
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Below is the code for the lift
void go_down()
{
//  digitalWrite(ENABLE,LOW);
//  digitalWrite(M0,HIGH);
//  digitalWrite(M1,LOW);
//  digitalWrite(M2,LOW);
  digitalWrite(RESET,HIGH);
  digitalWrite(SLEEP,HIGH);
  analogWrite(STEP,225);
  digitalWrite(DIR,HIGH);
  //digitalWrite(FAULT,HIGH);

  
}
void go_up()
{
//  digitalWrite(ENABLE,LOW);
//  digitalWrite(M0,HIGH);
//  digitalWrite(M1,LOW);
//  digitalWrite(M2,LOW);
  digitalWrite(RESET,HIGH);
  digitalWrite(SLEEP,HIGH);
  analogWrite(STEP,225);
  digitalWrite(DIR,LOW);
  //digitalWrite(FAULT,HIGH); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// below is the code for the shooter

void shoot()
{
  //digitalWrite(EN,HIGH); // Turn EN high
  analogWrite(M1IN1,250); // Set PWM speed for M1IN1
  analogRead(EncoderA1); // Read Encoder A for motor 1
  //digitalRead(EN); // Check if EN is high or low
  analogWrite(M1IN2,0); // Ser PWM speed for M1IN2
  digitalWrite(M1D1,LOW); //Set M1D1 low
  digitalRead(M1D1); // Check if M1D1 is low or high
  digitalWrite(M1D2,HIGH); // Set M1D2 High
  //analogRead(M1SF); // check to see if M1SF is low or high
  
  analogWrite(M2IN1,0); // Set PWM speed for M2IN1
  analogRead(EncoderA2); // Read Encoder A for motor 2
  analogWrite(M2IN2,250); // Set PWM speed for M2IN2
  digitalWrite(M2D1,LOW); //Set M2D1 low
  digitalRead(M2D1); // Check the state of M2D1
  digitalWrite(M2D2,HIGH); //Set M2D2 High
  digitalRead(M2D2); // Check State of M2D2
  //analogRead(M2SF); // Check state of M2SF
  
  
  
}
void halt_lift()
{
//  digitalWrite(ENABLE,LOW);
//  digitalWrite(M0,HIGH);
//  digitalWrite(M1,LOW);
//  digitalWrite(M2,LOW);
  digitalWrite(RESET,HIGH);
  digitalWrite(SLEEP,HIGH);
  analogWrite(STEP,0);
  digitalWrite(DIR,HIGH);
  //digitalWrite(FAULT,HIGH);

  
}
void halt_shoot()
{
  //digitalWrite(EN,HIGH); // Turn EN high
  analogWrite(M1IN1,0); // Set PWM speed for M1IN1
  analogRead(EncoderA1); // Read Encoder A for motor 1
  //digitalRead(EN); // Check if EN is high or low
  analogWrite(M1IN2,0); // Ser PWM speed for M1IN2
  digitalWrite(M1D1,LOW); //Set M1D1 low
  digitalRead(M1D1); // Check if M1D1 is low or high
  digitalWrite(M1D2,HIGH); // Set M1D2 High
  //analogRead(M1SF); // check to see if M1SF is low or high
  
  analogWrite(M2IN1,0); // Set PWM speed for M2IN1
  analogRead(EncoderA2); // Read Encoder A for motor 2
  analogWrite(M2IN2,0); // Set PWM speed for M2IN2
  digitalWrite(M2D1,LOW); //Set M2D1 low
  digitalRead(M2D1); // Check the state of M2D1
  digitalWrite(M2D2,HIGH); //Set M2D2 High
  digitalRead(M2D2); // Check State of M2D2
  //analogRead(M2SF); // Check state of M2SF
  
  
  
}
void piston_extend()
{
  digitalWrite(EN7,HIGH);  //  Turn EN7 on
  digitalWrite(EXTEND,HIGH);  //  Set EXTEND high to extend piston
  digitalWrite(RETRACT,LOW);  //  Set RETRACT low
  
  
}
void piston_retract()
{
  digitalWrite(EN7,HIGH);  //  Turn EN7 on
  digitalWrite(EXTEND,LOW);  //  Set EXTEND low
  digitalWrite(RETRACT,HIGH);  //  Set RETRACT high to retract piston
  
  
  
}
void halt_piston()
{
  digitalWrite(EN7,HIGH);  //  Turn EN7 off
  digitalWrite(EXTEND,LOW);  //  Set EXTEND low
  digitalWrite(RETRACT,LOW);  //  Set RETRACT low
  
  
}
