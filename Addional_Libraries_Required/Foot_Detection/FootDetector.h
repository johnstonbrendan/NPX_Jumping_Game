#ifndef ARDUINO
#define ARDUINO 101
#endif

#ifndef FootDetector_h
#define FootDetector_h


#include "SR04.h" //just leave this error from the compilier about WProgram, it still works


class FootDetector{
    public:
        FootDetector(int triggerPin, int echoPin, long footDist, long noFootDist);
        ~FootDetector();
        bool FootDetected();
        long GetDistance();
    private:
        long distance;
        SR04 * UltraSensor;
        long footDistance;
        long noFootDistance;
};


#endif