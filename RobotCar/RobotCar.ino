#include <IRremoteInt.h>
#include <IRremote.h>
#include <Servo.h>
#include "RobotController.h"

/*
 IRemote library being used: https://github.com/z3t0/Arduino-IRremote/wiki
*/

IRrecv irrecv(11); // Receive on pin 11
decode_results results;

Servo myServo;

RobotController mrRobot;
bool foo = false;

void WarmUpMotor()
{
    if (false == foo)
    {
        mrRobot.Forward();
        delay(2000);
        foo = true;
    }
    else
    {
        mrRobot.Reverse();
        delay(2000);
        foo = false;
    }
}

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    mrRobot.init();
    WarmUpMotor();
    WarmUpMotor();
    mrRobot.Stop();
}

void loop()
{

    
   if (irrecv.decode(&results)) 
    {
        
       /* if (results.value == (unsigned long) 0x3D9AE3F7)
        {
            Serial.println("Forward");
            mrRobot.Forward();
        }
        if (results.value == (unsigned long)0xFF18E7)
        {
            Serial.println("Forward two");
            mrRobot.Forward();
        }*/
        mrRobot.ProcessInput((uint32_t)results.value);
        irrecv.resume(); // Continue receiving
    } 
}


