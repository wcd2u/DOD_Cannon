#include <QTRSensors.h>


#define NUM_SENSORS_MAIN 5
//#define NUM_SENSORS_AUX 2
#define TIMEOUT 2500
#define NUM_SAMPLES_PER_SENSOR 4

int motor_speed = 50;
int threshold[NUM_SENSORS_MAIN] = {650, 525, 502, 499, 675};
int turnDelay = 0;

// Set the integers for Motors 3 & 4

//int ENA = 26;
int M1IN1A = 9;
int M1IN2A = 8;
//int M1FBA = A0;
int EncoderA1A = A1;
int EncoderB1A = A2;
//int INVA = 28;
//int M1SFA = A3;
int M1D1A = 32;
int M1D2A = 30;

//int SLEWA = 27;

int M2D1A = 36;
int M2D2A = 34;
//int M2SFA = 31;
//int M2FBA = 32;
int EncoderA2A = A4;
int EncoderB2A = A5;
int M2IN1A = 11;
int M2IN2A = 10;

// Set the integers for Motors 1 & 2

//int ENB = 40;
int M1IN1B = 3;
int M1IN2B = 4;
//int M1FBB = A9;
int EncoderA1B = A10;
int EncoderB1B = A11;
//int INVB = 35;
//int M1SFB = A8;
int M1D1B = 44;
int M1D2B = 42;

//int SLEWB = 41;

int M2D1B = 48;
int M2D2B = 46;
//int M2SFB = 48;
//int M2FBB = 49;
int EncoderA2B = A12;
int EncoderB2B = A13;
int M2IN1B = 5;
int M2IN2B = 2;

int incomingByte = 0;
int turnFlag = 0;
int stage = 'm';

QTRSensorsAnalog sensorsMain((unsigned char[]) {A8, A9, A10, A11, A12}, NUM_SENSORS_MAIN, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int mainValues[NUM_SENSORS_MAIN];


void setup() {
 // put your setup code here, to run once:
 // A side( Right Side)
 pinMode(M1IN1A,OUTPUT); // PWM for M1IN1 to move forward
 pinMode(M1IN2A,OUTPUT); // PWM for M1IN2 to move backwards
 //pinMode(M1FBA,INPUT); // Analog read for M1FB of H-Bridge
 pinMode(EncoderA1A,INPUT); // Analog read for Encoder A output on motor 1
 pinMode(EncoderB1A,INPUT); // Analog read for Encoder B output on motor 1
 //pinMode(ENA,OUTPUT); // Digital input for EN to enable motor driver
 //pinMode(INVA,OUTPUT); // Digital input for INV to inverse outputs of M1IN's
 //pinMode(M1SFA,INPUT); // Analog input for M1SF
 pinMode(M1D1A,OUTPUT); // Digital input for M1D1
 pinMode(M1D2A,OUTPUT); // Digital input for M1D2
 //pinMode(SLEWA,OUTPUT); // Digital input for SLEW
 pinMode(M2IN1A,OUTPUT); // PWM for M2IN1 to move forward
 pinMode(M2IN2A,OUTPUT); // PWM for M2IN2 to move backwards
 //pinMode(M2FBA,INPUT); // Analog read for M2FB of H-Bridge
 pinMode(EncoderA2A,INPUT); // Analog read for Encoder A output on motor 2
 pinMode(EncoderB2A,INPUT); // Analog read for Encoder B output on motor 2
 pinMode(M2D1A,OUTPUT); // Digital input for M2D1
 pinMode(M2D2A,OUTPUT); // Digital input for M2D2
 //pinMode(M2SFA,INPUT); // Analog input for M2SF
 
 // B side( Left Side)
 pinMode(M1IN1B,OUTPUT); // PWM for M1IN1 to move forward
 pinMode(M1IN2B,OUTPUT); // PWM for M1IN2 to move backwards
 //pinMode(M1FBB,INPUT); // Analog read for M1FB of H-Bridge
 pinMode(EncoderA1B,INPUT); // Analog read for Encoder A output on motor 1
 pinMode(EncoderB1B,INPUT); // Analog read for Encoder B output on motor 1
 //pinMode(ENB,OUTPUT); // Digital input for EN to enable motor driver
 //pinMode(INVB,OUTPUT); // Digital input for INV to inverse outputs of M1IN's
 //pinMode(M1SFB,INPUT); // Analog input for M1SF
 pinMode(M1D1B,OUTPUT); // Digital input for M1D1
 pinMode(M1D2B,OUTPUT); // Digital input for M1D2
 //pinMode(SLEWB,OUTPUT); // Digital input for SLEW
 pinMode(M2IN1B,OUTPUT); // PWM for M2IN1 to move forward
 pinMode(M2IN2B,OUTPUT); // PWM for M2IN2 to move backwards
 //pinMode(M2FBB,INPUT); // Analog read for M2FB of H-Bridge
 pinMode(EncoderA2B,INPUT); // Analog read for Encoder A output on motor 2
 pinMode(EncoderB2B,INPUT); // Analog read for Encoder B out[ut on motor 2
 pinMode(M2D1B,OUTPUT); // Digital input for M2D1
 pinMode(M2D2B,OUTPUT); // Digital input for M2D2
 //pinMode(M2SFB,INPUT); // Analog input for M2SF
 
 Serial.begin(57600);
 Serial.setTimeout(500);

 incomingByte = 0;
 
 
 

}

void loop() {
 // put your main code here, to run repeatedly:
 
 if(Serial.available()==0) {
//   incomingByte = Serial.read();
   //Serial.print(incomingByte);
   //Serial.print(' ');
   
//   if (incomingByte == 'a') {
//     move_forward(motor_speed);
//   }
//   if (incomingByte == 'b') {
//     move_backward(motor_speed);
//   }
//   if (incomingByte == 'c') {
//     translate_left(motor_speed);
//   }
//   if (incomingByte == 'd') {
//     translate_right(motor_speed);
//   }
//   if (incomingByte == 'e') {
//     rotate_CCW(motor_speed);
//   }
//   if (incomingByte == 'f') {
//     rotate_CW(motor_speed);
//   }
//   if (incomingByte == 'k') {
//     diagonal_FL(motor_speed);
//   }
//   if (incomingByte == 'l') {
//     diagonal_FR(motor_speed);
//   }
//   if (incomingByte == 'm') {
//     diagonal_BL(motor_speed);
//   }
//   if (incomingByte == 'n') {
//     diagonal_BR(motor_speed);
//   }
//   if (incomingByte == 'z') {
//     halt();
//   }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is for getting to the start of the line    
    while (stage == 's') {
      mainValues[NUM_SENSORS_MAIN] = {values()};
      // If not at the start line move forward      
      while ((mainValues[0] != 1) and (mainValues[4] != 1) and (stage == 's')) { 
        move_forward(motor_speed);
        mainValues[NUM_SENSORS_MAIN] = {values()};
      }
      halt();
      delay(3000);
      // If the Sensor 0 hits the line first rotate until sensor 4 is also on the line
      if (mainValues[0] == 1) {
        while ((mainValues[0] == 1) and (mainValues[4] == 0) and (stage == 's')) {
          rotate_CCW(motor_speed);
          mainValues[NUM_SENSORS_MAIN] = {values()};
        }
      }
      // If the Sensor 4 hits the line first rotate until Sensor 0 is also in the line
      if (mainValues[4] == 1) {
        while ((mainValues[4] == 1) and (mainValues[0] == 0) and (stage == 's')) {
          rotate_CW(motor_speed);
          mainValues[NUM_SENSORS_MAIN] = {values()};
        }
      }
      halt();
      delay(3000);
      // Once both 0 and 4 sensors are on the line move forward
      while ((mainValues[0] == 1) or (mainValues[4] == 1) and (stage == 's')) {
        move_forward(motor_speed);
        mainValues[NUM_SENSORS_MAIN] = {values()};
      }
      move_forward(motor_speed);
      delay(100);
      halt();
      delay(3000);
      // Adjust robot once pass the starting line line so that robot is in the middle of the line
      while (((mainValues[1] == 1) or (mainValues[3] == 1)) and (stage == 's')) {
        if ((mainValues[1] == 1) or (mainValues[0] == 1)) {
          translate_left(motor_speed);
        }
        if ((mainValues[3] == 1) or (mainValues[4] == 1)) {
          translate_right(motor_speed);
        }
        mainValues[NUM_SENSORS_MAIN] = {values()};
      }
      turnFlag = 0;
      delay(3000);
      stage = 'm';// Send signal to let know that it is centered and in the middle portion of the course
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Middle Phase of line following
    while (stage == 'm') {
      mainValues[NUM_SENSORS_MAIN] = {values()};

      // While on the middle of the line
      while ((mainValues[2] == 1) and (stage == 'm')) {
        // Condition for moving forward
        if ((mainValues[1]==0) and (mainValues[3]==0) and (mainValues[0]==0) and (mainValues[4]==0)) {
          move_forward(motor_speed);
        }
//        // Condition for if veering left
//        if ((mainValues[1]!=0) and (mainValues[3]==0) and (mainValues[0]==0) and (mainValues[4]==0)) {
//          translate_right(motor_speed);
//        }
//        // Condition for if veering right
//        if ((mainValues[1]==0) and (mainValues[3]!=0) and (mainValues[0]==0) and (mainValues[4]==0)) {
//          translate_left(motor_speed);
//        }
        // Condition for 90 degree right turn
        if (mainValues[0] == 1) {
          turnFlag = 1;
        }
        if (mainValues[4] == 1) {
          turnFlag = 2;
        }
        while ((turnFlag != 0) and (mainValues[2] == 1)) {
          move_forward(motor_speed);
          mainValues[NUM_SENSORS_MAIN] = {values()};
          turnDelay = 500;
        }
        while (turnDelay != 0) {
          move_forward(motor_speed);
          delay(turnDelay);
          halt();
          turnDelay = 0;
        }
        while ((turnFlag != 0) and (mainValues[2] != 1)) {
          if (turnFlag == 1) {
            front_pivot_CCW(motor_speed);
          }
          if (turnFlag == 2) {
            front_pivot_CW(motor_speed);
          }
          mainValues[NUM_SENSORS_MAIN] = {values()};
        }
        turnFlag = 0;
//        if ((mainValues[1]==0) and (mainValues[3]!=0) and (mainValues[0]==0) and (mainValues[4]!=0)) {
//          rotate_CW(motor_speed);
//        }
        // Condition for 90 degree left turn
//        if ((mainValues[1]!=0) and (mainValues[3]==0) and (mainValues[0]!=0) and (mainValues[4]==0)) {
//          rotate_CCW(motor_speed);
//        }
//        // Condition for greater than 90 degree right turn
//        if ((mainValues[1]==0) and (mainValues[3]!=0) and (mainValues[0]==0) and (mainValues[4]==0)) {
//          rotate_CW(motor_speed);
//        }
//        // Condition for greater than 90 degree left turn
//        if ((mainValues[1]!=0) and (mainValues[3]==0) and (mainValues[0]==0) and (mainValues[4]==0)) {
//          rotate_CCW(motor_speed);
//        }
        // Condition for less than 90 degree right turn
        if ((mainValues[1]==0) and (mainValues[3]==0) and (mainValues[0]!=0) and (mainValues[4]==0)) {
          rotate_CW(motor_speed);
        }
        // Condition for less than 90 degree left turn
        if ((mainValues[1]==0) and (mainValues[3]==0) and (mainValues[0]==0) and (mainValues[4]!=0)) {
          rotate_CCW(motor_speed);
        }
        // Condition for when at the finish line
        if ((mainValues[0]!=0) and (mainValues[1]!=0) and (mainValues[3]!=0) and (mainValues[4]!=0)) {
          move_forward(motor_speed);
        }
        
        mainValues[NUM_SENSORS_MAIN] = {values()};
      }
    }
      stage = 'e';// Send signal to let know that it is centered and at the end portion of the course
//////////////////////////////////////////////////////////////////////////////////////////////////////     
// End portion of the line   
   while (stage == 'e') {

      // Once pass the finish line go back and check to make sure
        // Condition for moving backwards
        if ((mainValues[1]==0) and (mainValues[3]==0) and (mainValues[0]==0) and (mainValues[4]==0)) {
          move_backward(motor_speed);
          }
        while((mainValues[0]!=0) and (stage == 'e')){
          rotate_CW(motor_speed);
        }

 }
 }
}
void move_backward(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,motor_speed); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,motor_speed); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left)
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,motor_speed); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,motor_speed); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void move_forward(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,motor_speed); // Set PWM speed for M1IN1; [Back Left] (Back Right)
 analogRead(EncoderA1A); // Read Encoder A
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Set PWM speed for M1IN2; [Back Left] (Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,motor_speed); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left)
 analogRead(EncoderA1B); // Read Encoder A
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Set PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,motor_speed); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
}

void rotate_CCW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,motor_speed); // Set PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,motor_speed); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right direction is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,motor_speed); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,motor_speed); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}

void rotate_CW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,motor_speed); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,motor_speed); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,motor_speed); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}

void translate_left(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,motor_speed); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,motor_speed); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,motor_speed); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,motor_speed); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}

void translate_right(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,motor_speed); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,motor_speed); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,motor_speed); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void halt()
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,LOW); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,LOW); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void diagonal_FL(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,motor_speed); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,motor_speed); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void diagonal_FR(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,motor_speed); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void diagonal_BL(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,motor_speed); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void diagonal_BR(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,motor_speed); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,motor_speed); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void front_pivot_CCW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,motor_speed); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,motor_speed); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void front_pivot_CW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,motor_speed); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,motor_speed); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}

void back_pivot_CCW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,0); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,motor_speed); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,0); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,motor_speed); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}
void back_pivot_CW(int motor_speed)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,motor_speed); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,0); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,motor_speed); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,0); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,0); // Set PWM speed for M1IN1; [Back Right](Front Left) Back Right is reversed
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,0); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,0); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,0); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
 
 
}

unsigned int values()
{
  sensorsMain.read(mainValues);
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
    if (mainValues[i] < threshold[i]) {
      mainValues[i] = 0;
    }
    else {
      mainValues[i] = 1;
    }
  }
  return mainValues;
}
