// RobotController.h

#ifndef _ROBOTCONTROLLER_h
#define _ROBOTCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum MotorState
{
    Stop,
    Forward,
    Reverse,
    Right,
    Left
};
class RobotController
{
 public:
	void init();
    void Forward();
    void Reverse();
    void Right();
    void Left();
    void Stop();
    void ProcessInput(uint32_t value);

private:
    MotorState m_MotorState;
};

#endif

