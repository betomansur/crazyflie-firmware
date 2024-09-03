#include "mbed.h"
#include "crazyflie.h"
#include "src/utils/parameters.h"

PwmOut motor(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);


float control_motor(float w)
{
  float pwm = (a2*w*w) + (a1*w); 
  return pwm;
}

int main()
{
    while (true)
    {
            // Loop infinito, o código pode ser expandido aqui
        motor.period(1.0/500.0);
        motor = control_motor(1600.0);
        motor2.period(1.0/500.0);
        motor2 = control_motor(1600.0);
        motor3.period(1.0/500.0);
        motor3 = control_motor(1600.0);
        motor4.period(1.0/500.0);
        motor4 = control_motor(1600.0);
        wait(5.0);
        motor = control_motor(0.0);
        motor2 = control_motor(0.0);
        motor3 = control_motor(0.0);
        motor4 = control_motor(0.0);
        wait(5.0);
    }
}
