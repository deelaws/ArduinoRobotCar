// 
// Robot Controller Source File
// 
#include "RobotController.h"

int ENA = 5;//connected to Arduino's port 5(output pwm)
int IN1 = 2;//connected to Arduino's port 2
int IN2 = 3;//connected to Arduino's port 3
int ENB = 6;//connected to Arduino's port 6(output pwm)
int IN3 = 4;//connected to Arduino's port 4
int IN4 = 7;//connected to Arduino's port 7

#define REMOTE_INPUT_TWO    (uint32_t) 0xFF18E7
#define REMOTE_INPUT_EIGHT  (uint32_t) 0xFF4AB5
#define REMOTE_INPUT_SIX    (uint32_t) 0xFF5AA5
#define REMOTE_INPUT_FOUR   (uint32_t) 0xFF10EF
#define REMOTE_INPUT_FIVE   (uint32_t) 0xFF38C7


void RobotController::init()
{
    this->m_MotorState = MotorState::Stop;
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
}


void RobotController::Forward()
{
    this->m_MotorState = MotorState::Forward;
    Serial.println("Forward");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);//setting motorA's directon

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);//setting motorB's directon

    analogWrite(ENA, 255);//start driving motorA
    analogWrite(ENB, 255);//start driving motorB
}

void RobotController::Stop()
{
    this->m_MotorState = MotorState::Stop;
    Serial.println("Stop");
    analogWrite(ENA, 0);//start driving motorA
    analogWrite(ENB, 0);//start driving motorB
}

void RobotController::Reverse()
{
    this->m_MotorState = MotorState::Reverse;
    Serial.println("Reverse");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);//setting motorA's directon

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);//setting motorB's directon

    analogWrite(ENA, 255);//start driving motorA
    analogWrite(ENB, 255);//start driving motorB
}

void RobotController::Right()
{
    this->m_MotorState = MotorState::Right;
    Serial.println("Right");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);//setting motorA's directon

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);//setting motorB's directon

    analogWrite(ENA, 255);//start driving motorA
    analogWrite(ENB, 255);//start driving motorB
}

void RobotController::Left()
{
    this->m_MotorState = MotorState::Left;
    Serial.println("Left");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);//setting motorA's directon

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);//setting motorB's directon

    analogWrite(ENA, 255);//start driving motorA
    analogWrite(ENB, 255);//start driving motorB
}

void RobotController::ProcessInput(uint32_t value)
{
    Serial.println(value, HEX);
    switch (value)
    {
        case REMOTE_INPUT_TWO:
            this->Forward();
            break;
        case REMOTE_INPUT_SIX:
            this->Right();
            break;
        case REMOTE_INPUT_EIGHT:
            this->Reverse();
            break;
        case REMOTE_INPUT_FOUR:
            this->Left();
            break;
        case REMOTE_INPUT_FIVE:
            this->Stop();
            break;
        default:
            //this->Stop();
            break;
    }

    return;
}