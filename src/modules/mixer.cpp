#include "crazyflie.h"
#include "mixer.h"

// Class constructor
Mixer::Mixer() 
    : motor_1(MOTOR1), motor_2(MOTOR2), motor_3(MOTOR3), motor_4(MOTOR4),
      led_verdeL(LED_GREEN_L), led_verdeR(LED_GREEN_R), 
      led_vermL(LED_RED_L), led_vermR(LED_RED_R), armed(false)
{
    motor_1.period(1.0/500.0); // Set PWM frequency to 500 Hz
    motor_2.period(1.0/500.0);
    motor_3.period(1.0/500.0);
    motor_4.period(1.0/500.0);
    motor_1 = 0.0; // Initialize motor signals to zero
    motor_2 = 0.0;
    motor_3 = 0.0;
    motor_4 = 0.0;
}

// Arm function: Enables the motors and indicates armed state with LEDs
void Mixer::arm()
{
    armed = true;
    led_vermL = 1; // Turn on red LEDs
    led_vermR = 1;
}

// Disarm function: Disables the motors and indicates disarmed state with LEDs
void Mixer::disarm()
{
    actuate(0, 0, 0, 0);
    armed = false;
    led_vermL = 0; // Turn off red LEDs
    led_vermR = 0;
}

// Actuate motors with desired total thrust force (N) and torques (N.m)
void Mixer::actuate(float f_t, float tau_phi, float tau_theta, float tau_psi)
{
    if (armed) {
        mixer(f_t, tau_phi, tau_theta, tau_psi);
        motor_1 = control_motor(omega_1);
        motor_2 = control_motor(omega_2);
        motor_3 = control_motor(omega_3);
        motor_4 = control_motor(omega_4);
    } 
}

// Convert total thrust force (N) and torques (N.m) to angular velocities (rad/s)
void Mixer::mixer(float f_t, float tau_phi, float tau_theta, float tau_psi)
{
    // Compute angular velocities squared for each motor
    float omega_1_squared = (f_t/(4 * kl)) - (tau_phi/(2 * kl * l)) - (tau_theta/(4 * kl * l)) - (tau_psi/(4 * kd));
    float omega_2_squared = (f_t/(4 * kl)) - (tau_phi/(2 * kl * l)) + (tau_theta/(4 * kl * l)) + (tau_psi/(4 * kd));
    float omega_3_squared = (f_t/(4 * kl)) + (tau_phi/(2 * kl * l)) + (tau_theta/(4 * kl * l)) - (tau_psi/(4 * kd));
    float omega_4_squared = (f_t/(4 * kl)) + (tau_phi/(2 * kl * l)) - (tau_theta/(4 * kl * l)) + (tau_psi/(4 * kd));

    // Ensure that angular velocities are non-negative
    omega_1 = sqrt(fmax(0.0, omega_1_squared));
    omega_2 = sqrt(fmax(0.0, omega_2_squared));
    omega_3 = sqrt(fmax(0.0, omega_3_squared));
    omega_4 = sqrt(fmax(0.0, omega_4_squared));
}

// Convert desired angular velocity (rad/s) to PWM signal (%)
float Mixer::control_motor(float omega)
{
    // PWM signal calculation using the motor model: PWM = a2 * omega^2 + a1 * omega
    float pwm_signal = a2 * omega * omega + a1 * omega;
    return pwm_signal;
}
