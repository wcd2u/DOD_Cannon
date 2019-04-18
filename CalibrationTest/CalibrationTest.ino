//Higher values mean lower reflectance

#include <QTRSensors.h>

#define NUM_SENSORS_MAIN 5
#define TIMEOUT 2500
#define NUM_SAMPLES_PER_SENSOR 4

QTRSensorsAnalog mainArray((unsigned char[]) {A8, A9, A10, A11, A12}, NUM_SENSORS_MAIN, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int mainValues[NUM_SENSORS_MAIN];

int threshold = 850;
int multiThresholdLow[NUM_SENSORS_MAIN] = {0, 0, 0, 0, 0};
int multiThresholdHigh[NUM_SENSORS_MAIN] = {0, 0, 0, 0, 0};

void setup() {
  mainValues[NUM_SENSORS_MAIN] = {values()};
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
    multiThresholdLow[i] = mainValues[i];
    multiThresholdHigh[i] = mainValues[i];
  }
    

  Serial.begin(57600);
}

void loop() {
  //unsigned int sensors[NUM_SENSORS_MAIN];
  //mainArray.read(mainValues);
  mainValues[NUM_SENSORS_MAIN] = {values()};
  for (unsigned char i = 0; i < NUM_SENSORS_MAIN; i++) {
    Serial.print(mainValues[i]);
    Serial.print('\t');
    if (multiThresholdLow[i] > mainValues[i]) {
      multiThresholdLow[i] = mainValues[i];
    }
    if (multiThresholdHigh[i] < mainValues[i]) {
      multiThresholdHigh[i] = mainValues[i];
    }
  }
  Serial.println();
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
    Serial.print(multiThresholdLow[i]);
    Serial.print('\t');
  }
  Serial.print("Low");
  Serial.println();

  for (unsigned char i = 0; i < NUM_SENSORS_MAIN; i++) {
    Serial.print(multiThresholdHigh[i]);
    Serial.print('\t');
  }
  Serial.print("High");
  Serial.println();
  delay(50);
}

unsigned int values()
{
  unsigned int result[NUM_SENSORS_MAIN];
  mainArray.read(mainValues);
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
//    if (mainValues[i] < threshold) {
//      mainValues[i] = 0;
//    }
//    if (mainValues[i] >= threshold) {
//      mainValues[i] = 1;
//    }
    result[i] = mainValues[i];
  }
  return result;
}
