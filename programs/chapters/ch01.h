// #include "mbed.h"
// #include "crazyflie.h"

// // Define all LEDs as digital output objects

// // Define all motors as PWM objects
// DigitalOut led_azul(LED_BLUE_L,!false);
// DigitalOut led_verm_dir(LED_RED_R,!false);
// DigitalOut led_verm_esq(LED_RED_L,!false);


// // Main program
// int main()
// {
//     // Blink blue LED indicating inicialization (5 seconds)

//     for (int i = 0; i < 10; ++i) {
//         led_azul = !led_azul;  
//         wait(0.5);     
//     }

//     wait(5);
    
//     // Turn on red LEDs indicating motors are armed
//     led_verm_dir = true;
//     led_verm_esq = true;
    
//     // Test all motors with different frequencies (to make different noises)
    
//     // Turn off red LEDs indicating motors are disarmed
    
//     // Blink green LEDs indicating end of program
//     while(true)
//     {
        
//     }
// }
#include "mbed.h"
#include "crazyflie.h"

// Define red LED (right) as digital output object
DigitalOut led(LED_GREEN_R,!false);

// Main program
int main()
{
    // Blink LED every second
    while(true) 
    {
        led = 1;
        wait(5);
    }
}
