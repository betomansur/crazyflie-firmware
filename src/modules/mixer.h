#ifndef mixer_h
#define mixer_h

#include "mbed.h"

// Mixer class
class Mixer {
public:
  // Class constructor
  Mixer();

  // Actuate motors with desired total trust force (N) and torques (N.m)
  void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi);

  // Função de inicialização do drone (pisca LEDs e motores) e então permite o acionamento (armed = true)
  void arm();  

  // Função que desarma motor (armed = false)
  void disarm();

private:
  // Motors PWM outputs
  PwmOut motor_1, motor_2, motor_3, motor_4;

  // Declaração de LEDs como outputs para mostrar status de operação
  DigitalOut led_verdeL, led_verdeR, led_vermL, led_vermR;

  // Angular velocities ( rad /s)
  float omega_1, omega_2, omega_3, omega_4;

  // Convert total thrust force (N) and torques (N.m) to angular velocities (rad/s)
  void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi);

  // Convert desired angular velocity (rad/s) to PWM signal (%)
  float control_motor(float omega);

  // Variável de controle do acionamento do motor
  bool armed;
};

#endif