#include "mbed.h"
#include "crazyflie.h"
#include "parameters.h"

PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

// função para converter velocidade angular em duty cycle do PWM
float control_motor(float omega)
{
    return a2*omega*omega + a1*omega; // função obtida experimentalmente 
}

int main()
{
    motor1.period(1.0/500.0); // frequencia do motor
    motor2.period(1.0/500.0); // frequencia do motor
    motor3.period(1.0/500.0); // frequencia do motor
    motor4.period(1.0/500.0); // frequencia do motor

    motor1 = control_motor(1000.0);
    motor2 = control_motor(2000.0);
    motor3 = control_motor(1000.0);
    motor4 = control_motor(2000.0);

    //motor = 0.1;
    wait(10);

    motor1 = 0.0;
    motor2 = 0.0;
    motor3 = 0.0;
    motor4 = 0.0;
}