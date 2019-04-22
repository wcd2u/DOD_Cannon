#include <QTRSensors.h>


#define NUM_SENSORS_MAIN 5
//#define NUM_SENSORS_AUX 2
#define TIMEOUT 2500
#define NUM_SAMPLES_PER_SENSOR 4

int threshold[NUM_SENSORS_MAIN] = {650, 575, 502, 575, 675};

// Set the integers for the left side A

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

// Set the integers for the right side B

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

int mode = 'm';
int data = 0;
int ballInRange = 0;
char wheel1[5];
char wheel2[5];
char wheel3[5];
char wheel4[5];

int w1f = 0;
int w1b = 0;
int w2f = 0;
int w2b = 0;
int w3f = 0;
int w3b = 0;
int w4f = 0;
int w4b = 0;
int motor_speed = 40;

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
 
 
 

}

void loop() {
  // put your main code here, to run repeatedly:

  if (mode == 'm') {
    
    if(Serial.available() > 0) {
  
      data = Serial.read();
      //Serial.println(data);
      if (data == '.') {
        //Serial.println("Read period.");
  
        //Serial.print("Data read: ");
        for (int i = 0; i < 4; i++) {
           while (Serial.available()==0){}
           data = Serial.read();
           //Serial.print(data);
           wheel1[i] = data;
           //Serial.print(wheel1[i]);
           //Serial.print(' ');
        }
        //Serial.println();
  
        for (int i = 0; i < 4; i++) {
           while (Serial.available()==0){}
           data = Serial.read();
           //Serial.print(data);
           wheel2[i] = data;
           //Serial.print(wheel2[i]);
           //Serial.print(' ');
        }
        for (int i = 0; i < 4; i++) {
           while (Serial.available()==0){}
           data = Serial.read();
           //Serial.print(data);
           wheel3[i] = data;
           //Serial.print(wheel3[i]);
           //Serial.print(' ');
        }
        for (int i = 0; i < 4; i++) {
           while (Serial.available()==0){}
           data = Serial.read();
           //Serial.print(data);
           wheel4[i] = data;
           //Serial.print(wheel4[i]);
           //Serial.print(' ');
        }
        //Serial.println("OK");
  //      Serial.println();
  //      Serial.print(wheel1);
  //      Serial.print(' ');
  //      Serial.print(wheel2);
  //      Serial.print(' ');
  //      Serial.print(wheel3);
  //      Serial.print(' ');
  //      Serial.print(wheel4);
  
        if (wheel1[0] == '0') {
          w1f = 0;
          w1b = m_speed(wheel1);
        }
        else {
          w1f = m_speed(wheel1);
          w1b = 0;
        }
        if (wheel2[0] == '0') {
          w2f = 0;
          w2b = m_speed(wheel2);
        }
        else {
          w2f = m_speed(wheel2);
          w2b = 0;
        }
        if (wheel3[0] == '0') {
          w3f = 0;
          w3b = m_speed(wheel3);
        }
        else {
          w3f = m_speed(wheel3);
          w3b = 0;
        }
        if (wheel4[0] == '0') {
          w4f = 0;
          w4b = m_speed(wheel4);
        }
        else {
          w4f = m_speed(wheel4);
          w4b = 0;
        }
        manual_move(w1f,w1b,w2f,w2b,w3f,w3b,w4f,w4b);
      }
      if (data == 'A') {
        mode = data;
      }
      
    }
    halt();
  }
  if (mode == 'A') {

    values(mainValues);
    while ((mainValues[0] == 0) and (mainValues[1] == 0) and (mainValues[2] == 0) and (mainValues[3] == 0) and (mainValues[4] == 0)) {
      halt();
      values(mainValues);
    }
    if (mainValues[2] == 1) {
      if ((mainValues[1] == 0) and (mainValues[3] == 0)) {
        move_forward(motor_speed);
      }
      if (mainValues[1] == 1) {
        move_forward(motor_speed);
        rotate_CCW(motor_speed);
      }
      if (mainValues[3] == 1) {
        move_forward(motor_speed);
        rotate_CW(motor_speed);
      }
    }
    //insert ball sensor to reduce speed
    if (BALLSENSOR1 and (ballInRange == 0)){
      motor_speed = motor_speed-15;
      ballInRange = 1;
    }
    if BALLSENSOR2 {
      halt();
      Serial.print('a')
      while (data != 'C') {
        data = Serial.read();
      }
      motor_speed = motor_speed + 15;
      ballInRange = 0;
    }
    if ((mainValues[0] == 1) and (mainValues[4] == 1)) {
      rotate_CW(motor_speed);
      delay(1000);
      while(mainValues[1] == 0) {
        rotate_CW(motor_speed);
        values(mainValues);
      }
      halt();
      while ((mainValues[0] == 0) and (mainValues[4] == 0)) {
        move_backward(motor_speed);
        values(mainValues);
      }
      if (mainValues[0] == 1) {

        while (mainValues[4] == 0) {
          rotate_CW(motor_speed);
          values(mainValues);
        }
      }
      if (mainValues[4] == 1) {

        while (mainValues[0] == 0) {
          rotate_CCW(motor_speed);
          values(mainValues);
        }
      }
      halt();
      Serial.print('E');
    }
    while (data != 'M') {
      data = Serial.read();
    }
  }
}
void manual_move(int m1f, int m1b, int m2f, int m2b, int m3f, int m3b, int m4f, int m4b)
{
 // A SIDE( Left Side)
 //digitalWrite(ENA,HIGH); // Turn EN high
 analogWrite(M1IN1A,m3f); // Set PWM speed for M1IN1;  [Back Left](Back Right)
 analogRead(EncoderA1A); // Read Encoder A for motor 1
 //digitalRead(ENA); // Check if EN is high or low
 analogWrite(M1IN2A,m3b); // Ser PWM speed for M1IN2; [Back Left](Back Right)
 digitalWrite(M1D1A,LOW); //Set M1D1 low
 digitalRead(M1D1A); // Check if M1D1 is low or high
 digitalWrite(M1D2A,HIGH); // Set M1D2 High
 //analogRead(M1SFA); // check to see if M1SF is low or high
 
 analogWrite(M2IN1A,m4b); // Set PWM speed for M2IN1; [Front Left](Front Right)
 analogRead(EncoderA2A); // Read Encoder A for motor 2
 analogWrite(M2IN2A,m4f); // Set PWM speed for M2IN2; [Front Left](Front Right)
 digitalWrite(M2D1A,LOW); //Set M2D1 low
 digitalRead(M2D1A); // Check the state of M2D1
 digitalWrite(M2D2A,HIGH); //Set M2D2 High
 digitalRead(M2D2A); // Check State of M2D2
 //analogRead(M2SFA); // Check state of M2SF
 
 // B SIDE( Right Side)
 //digitalWrite(ENB,HIGH); // Turn EN high
 analogWrite(M1IN1B,m1f); // Set PWM speed for M1IN1; [Back Right](Front Left)
 analogRead(EncoderA1B); // Read Encoder A for motor 1
 //digitalRead(ENB); // Check if EN is high or low
 analogWrite(M1IN2B,m1b); // Ser PWM speed for M1IN2; [Back Right](Front Left)
 digitalWrite(M1D1B,LOW); //Set M1D1 low
 digitalRead(M1D1B); // Check if M1D1 is low or high
 digitalWrite(M1D2B,HIGH); // Set M1D2 High
 //analogRead(M1SFB); // check to see if M1SF is low or high
 
 analogWrite(M2IN1B,m2b); // Set PWM speed for M2IN1; [Front Right](Back Left)
 analogRead(EncoderA2B); // Read Encoder A for motor 2
 analogWrite(M2IN2B,m2f); // Set PWM speed for M2IN2; [Front Right](Back Left)
 digitalWrite(M2D1B,LOW); //Set M2D1 low
 digitalRead(M2D1B); // Check the state of M2D1
 digitalWrite(M2D2B,HIGH); //Set M2D2 High
 digitalRead(M2D2B); // Check State of M2D2
 //analogRead(M2SFB); // Check state of M2SF
 
 
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

int m_speed(char x[5]) {

  int result = 0;
  int power = 2;

  for (int i = 1; i < 4; i++) {
    result = result + pow(10, power)*((int)x[i]-48);
    --power;
  }
  return result;
  
}

void values(unsigned int targetValues[NUM_SENSORS_MAIN])
{
  sensorsMain.read(targetValues);
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
    if (targetValues[i] < threshold[i]) {
      targetValues[i] = 0;
    }
    else {
      targetValues[i] = 1;
    }
  }
  return;
  
}
