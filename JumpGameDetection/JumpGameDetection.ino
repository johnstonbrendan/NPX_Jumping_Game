#include "FootDetector.h"
#define TRIG_PIN_1 12
#define TRIG_PIN_2 10
#define ECHO_PIN_1 11
#define ECHO_PIN_2 9
#define FOOT_DIST_1 45 //cm
#define FOOT_DIST_2 45 //cm
#define NO_FOOT_DIST_1 100 //cm
#define NO_FOOT_DIST_2 100 //cm

//below are definitions for testing
#define TESTING_MODE 0 //0 for off 1 for on, turns on print statements
#define NUMBER_OF_SENSORS 1 //only do 1 or 2

FootDetector Detector_1 = FootDetector(TRIG_PIN_1,ECHO_PIN_1,FOOT_DIST_1,NO_FOOT_DIST_1);
FootDetector Detector_2 = FootDetector(TRIG_PIN_2,ECHO_PIN_2,FOOT_DIST_2,NO_FOOT_DIST_2);
uint8_t buf[8] = {0};

void setup() {
  #if TESTING_MODE
  Serial.begin(9600);
  #endif
  Serial.begin(9600);
  delay(200);
  // put your setup code here, to run once:

}

int previous_jump = 0;
void loop() {
  // put your main code here, to run repeatedly:
#if TESTING_MODE
  long distance_1 = Detector_1.GetDistance();
  Serial.print("Distance 1: ");
  Serial.print(distance_1);
  Serial.println("cm");
#if NUMBER_OF_SENSORS == 2
  Serial.print("Distance 2: ");
  long distance_2 = Detector_2.GetDistance();
  Serial.print(distance_2);
  Serial.println("cm");
  delay(60);
#endif
  if(Detector_1.FootDetected()){
    Serial.println("Foot Detected (Detector 1)");
  }
  if(Detector_2.FootDetected()){
    Serial.println("Foot Detected (Detector 2)");
  }
#endif
  bool footDetected = Detector_1.FootDetected();
//  delay(60);
#if NUMBER_OF_SENSORS == 2
  footDetected |= Detector_2.FootDetected();
#endif
  if (footDetected){
    previous_jump++;
  }
  else if(previous_jump > 3){
  previous_jump = 0;
#if TESTING_MODE
    Serial.println("Send Key");
#endif
  buf[2] = 44;
  Serial.write(buf,8);
  releaseKey();
//  Serial.println("Send Space");
//  delay(60);
  }
#if NUMBER_OF_SENSORS == 2
//  delay(60);
#endif
}

void releaseKey(){
  buf[2] = 0;
  Serial.write(buf,8);
}
