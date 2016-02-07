#include <IRremoteInt.h>
#include <IRremote.h>
#include <Servo.h>
#include "RobotController.h"

/*
 IRemote library being used: https://github.com/z3t0/Arduino-IRremote/wiki
*/

using namespace RobotControl;

IRrecv irrecv(11); // Receive on pin 11
decode_results results;

RobotController mrRobot;

void TestMotors()
{
    int ENA = 5;//connected to Arduino's port 5(output pwm)
    int IN1 = 2;//connected to Arduino's port 2
    int IN2 = 3;//connected to Arduino's port 3
    int ENB = 6;//connected to Arduino's port 6(output pwm)
    int IN3 = 4;//connected to Arduino's port 4
    int IN4 = 7;//connected to Arduino's port 7

    pinMode(ENA, OUTPUT);//output
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);//stop driving

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);//setting motorA's directon

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);//setting motorB's directon

    analogWrite(ENA, 255); //start driving motorA
    analogWrite(ENB, 255); //start driving motorB

    delay(2000);
    analogWrite(ENA, 0); //start driving motorB
    analogWrite(ENB, 255); //start driving motorB
    delay(2000);
    analogWrite(ENA, 255); //start driving motorA
    analogWrite(ENB, 0); //start driving motorB
    delay(2000);
    analogWrite(ENB, 0); //start driving motorB
    analogWrite(ENA, 0); //start driving motorB

}

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    mrRobot.init();

    mrRobot.Spin(Speed::Medium, Direction::Left, 50);
    //mrRobot.Forward(Speed::Medium, 90, 20);
    //TestMotors();
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
//        mrRobot.ProcessInput((uint32_t)results.value);
        irrecv.resume(); // Continue receiving
    } 
}


