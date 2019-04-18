//Higher values mean lower reflectance

#include <QTRSensors.h>

#define NUM_SENSORS_MAIN 5
#define TIMEOUT 2500
#define NUM_SAMPLES_PER_SENSOR 4

QTRSensorsAnalog mainArray((unsigned char[]) {A8, A9, A10, A11, A12}, NUM_SENSORS_MAIN, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int mainValues[NUM_SENSORS_MAIN];

int threshold[NUM_SENSORS_MAIN] = {650, 525, 502, 499, 675};

void setup() 
{
  Serial.begin(57600);
}

void loop() {
  //unsigned int sensors[NUM_SENSORS_MAIN];
  //mainArray.read(mainValues);
  mainValues[NUM_SENSORS_MAIN] = {values()};
  for (unsigned char i = 0; i < NUM_SENSORS_MAIN; i++) {
    Serial.print(mainValues[i]);
    Serial.print('\t');
  }
  Serial.println();
  Serial.println();
  delay(50);
}

unsigned int values()
{
  unsigned int result[NUM_SENSORS_MAIN];
  mainArray.read(mainValues);
  for (unsigned int i = 0; i < NUM_SENSORS_MAIN; i++) {
//    if (mainValues[i] < threshold[i]) {
//      mainValues[i] = 0;
//    }
//    else {
//      mainValues[i] = 1;
//    }
    result[i] = mainValues[i];
  }
  return result;
}
