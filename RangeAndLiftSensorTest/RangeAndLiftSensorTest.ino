int rangeSensor = A13;
int liftSensor = A14;



void setup() {
  // put your setup code here, to run once:
  pinMode(rangeSensor,INPUT);
  pinMode(liftSensor,INPUT);

  Serial.begin(57600);
  Serial.setTimeout(500);

}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.print(digitalRead(rangeSensor));
    Serial.print('\t');
    Serial.println(digitalRead(liftSensor));

}
