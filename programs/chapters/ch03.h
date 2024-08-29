#include "mbed.h"
#include "crazyflie.h"
#include "src/utils/parameters.h"

PwmOut motor(MOTOR1);

float control_motor(float w)
{
  float pwm = (a2*w*w) + (a1*w); 
  return pwm;
}

int main()
{
    motor.period(1.0/500.0);
    motor = control_motor(1000.0);
    wait(10);
    motor = 0.0;
    while (true)
    {
        // Loop infinito, o código pode ser expandido aqui
    }
}
