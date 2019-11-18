#include "FootDetector.h"

FootDetector::FootDetector(int triggerPin, int echoPin, long footDist, long noFootDist){
    UltraSensor = new SR04(echoPin,triggerPin);
    footDistance = footDist;
    noFootDistance = noFootDist;
}

long FootDetector::GetDistance(){
    distance =  UltraSensor->Distance();
    return distance;
}

bool FootDetector::FootDetected(){
    distance = UltraSensor->Distance();//returns centimeters
    return (distance < footDistance);
}

FootDetector::~FootDetector(){
    free(UltraSensor);
}