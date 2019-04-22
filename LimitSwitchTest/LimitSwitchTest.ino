int upperLimit = 46;
int lowerLimit = 48;
int upper = 0;
int lower = 0;



void setup() {
  pinMode(upperLimit,INPUT);
  pinMode(lowerLimit,INPUT);

  Serial.begin(57600);
  Serial.setTimeout(500);
}

void loop() {
  //if (Serial.available() > 0) {
    upper = digitalRead(upperLimit);
    lower = digitalRead(lowerLimit);
    Serial.print("Upper");
    Serial.print('\t');
    Serial.println("Lower");
    if (upper == 1) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
    Serial.print('\t');
    if (lower == 1) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
    Serial.println();
  //}
}
