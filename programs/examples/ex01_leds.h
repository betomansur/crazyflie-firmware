#include "mbed.h"
#include "crazyflie.h"

// Define red LED (right) as digital output object
DigitalOut led(LED_RED_R,!false);

// Main program
int main()
{
    // Blink LED every second
    while(true) 
    {
        led = true;
        wait(10);
        led = false;
    }
}
