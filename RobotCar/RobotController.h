// RobotController.h

#ifndef _ROBOTCONTROLLER_h
#define _ROBOTCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace RobotControl
{
    // Supporting three motor speeds currently
    enum Speed
    {
        Slow = 25,
        Medium = 55,
        Fast = 85,
        Insane = 100 // >.< Gotta love Teslas
    };

    enum Motors
    {
        LeftMotor,
        RightMotor
    };

    enum Direction
    {
        Left,
        Right
    };

    class RobotController
    {
    public:
        void init();

        // Degree can range from -90 to 90
        void Forward(Speed sp, uint8_t degree, uint8_t duration);
        void Reverse(Speed sp, uint8_t degree);
        void Stop();
        void Spin(Speed sp, Direction dir, uint8_t duration);
        void ProcessInput(uint32_t value);
    };
}
#endif

