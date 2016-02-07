// 
// Robot Controller Source File
// 
#include "RobotController.h"

using namespace RobotControl;

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

// 90 would be straight, 0 would be complete left and 180 would be complete right(Essentialy right turn)
#define OUT_OF_RANGE(x) (x > 180 || x <= 0)
#define MOTOR_FULL_POWER    0xFF


void RobotController::init()
{
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



// Speed can range from 0-100. 100 = full throttle
uint8_t CalculateDutyCycle(uint8_t speed, Motors mo, uint8_t degree)
{
    uint8_t ret = MOTOR_FULL_POWER;

    if ((Motors::LeftMotor == mo && degree < 90) || 
        (Motors::RightMotor == mo && degree > 90))
    {

            ret = (MOTOR_FULL_POWER * degree) / 90;
    }

    // Adjust for Speed and ret value
    return ((ret * speed) / 100);
}

void RobotController::Spin(Speed sp, Direction dir, uint8_t duration)
{
    uint8_t leftPower = MOTOR_FULL_POWER;
    uint8_t rightPower = MOTOR_FULL_POWER;

    if (dir == Direction::Left)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);//setting motorA's directon

        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);//setting motorB's directon
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);//setting motorA's directon

        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);//setting motorB's directon
    }

    Serial.print( leftPower, DEC);
    Serial.print(rightPower, DEC);

    analogWrite(ENA, (leftPower * sp) /100); //start driving motorA
    analogWrite(ENB, (rightPower * sp) /100); //start driving motorB
    delay(100 * duration);
    this->Stop();
}

void RobotController::Forward(Speed sp, uint8_t degree, uint8_t duration)
{
    uint8_t leftPower = 0;
    uint8_t rightPower = 0;
    if (!OUT_OF_RANGE(degree))
    {
        leftPower = CalculateDutyCycle(sp, Motors::LeftMotor, degree);
        rightPower = CalculateDutyCycle(sp, Motors::RightMotor, degree);

        Serial.println("Forward");
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);//setting motorA's directon

        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);//setting motorB's directon

        analogWrite(ENA, leftPower); //start driving motorA
        analogWrite(ENB, rightPower); //start driving motorB

        delay(100 * duration);
        this->Stop();
    }
}

void RobotController::Stop()
{
    Serial.println("Stop");
    analogWrite(ENA, 0);//start driving motorA
    analogWrite(ENB, 0);//start driving motorB
}

void RobotController::Reverse(Speed sp, uint8_t degree)
{
    uint8_t leftPower = 0;
    uint8_t rightPower = 0;

    if (!OUT_OF_RANGE(degree))
    {
        leftPower = CalculateDutyCycle(sp, Motors::LeftMotor, degree);
        rightPower = CalculateDutyCycle(sp, Motors::RightMotor, degree);
        Serial.println("Reverse");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW); //setting motorA's directon

        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW); //setting motorB's directon

        analogWrite(ENA, leftPower); //start driving motorA
        analogWrite(ENB, rightPower); //start driving motorB
    }
}


void RobotController::ProcessInput(uint32_t value)
{
    Serial.println(value, HEX);
    switch (value)
    {
        case REMOTE_INPUT_TWO:
            this->Forward(Speed::Fast, 90, 20);
            break;
        case REMOTE_INPUT_SIX:
            // Turn Right
            this->Forward(Speed::Fast, 135,20);
            break;
        case REMOTE_INPUT_EIGHT:

            this->Reverse(Speed::Fast, 90);
            break;
        case REMOTE_INPUT_FOUR:
            this->Forward(Speed::Fast, 45,20);
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