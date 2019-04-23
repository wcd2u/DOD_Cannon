int ledRed = 31;
int ledGreen = 33;
int ledBlue = 35;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledBlue,OUTPUT);

  Serial.begin(57600);
  Serial.setTimeout(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  redLight();
  delay(1000);
  greenLight();
  delay(1000);
  blueLight();
  delay(1000);
  purpleLight();
  delay(1000);
  yellowLight();
  delay(1000);
  cyanLight();
  delay(1000);

}

void redLight() {
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledBlue,LOW);
}

void greenLight() {
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue,LOW);
}

void blueLight() {
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledBlue,HIGH);
}

void purpleLight() {
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledBlue,HIGH);
}
void yellowLight() {
  digitalWrite(ledRed,HIGH);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue,LOW);
}
void cyanLight() {
  digitalWrite(ledRed,LOW);
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledBlue,HIGH);
}
