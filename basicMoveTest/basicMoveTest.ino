#include <QTRSensors.h>


#define NUM_SENSORS_MAIN 5
//#define NUM_SENSORS_AUX 2
#define TIMEOUT 2500
#define NUM_SAMPLES_PER_SENSOR 4

int motor_speed = 40;
int threshold[NUM_SENSORS_MAIN] = {890, 875, 805, 805, 910};

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
int stage = 0;

//QTRSensorsAnalog sensorsMain((unsigned char[]) {A8, A9, A10, A11, A12}, NUM_SENSORS_MAIN, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
//unsigned int mainValues[NUM_SENSORS_MAIN];


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

 incomingByte = 's';
 
 
 

}

void loop()
{
  move_forward(motor_speed);
  delay(2000);
  move_backward(motor_speed);
  delay(2000);
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
