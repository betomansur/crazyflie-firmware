#ifndef attitude_estimator_h
#define attitude_estimator_h

#include "mbed.h"
#include "crazyflie.h"

// Classe do estimador de atitude
class AttitudeEstimator {
public:
    // Construtor da classe
    AttitudeEstimator();

    // Inicializa a classe
    void init();

    // Estima ângulos de Euler (rad) e velocidades angulares (rad/s)
    void estimate();

    // Atributos públicos: ângulos de Euler (rad)
    float phi, theta, psi;

    // Atributos públicos: velocidades angulares (rad/s)
    float p, q, r;

private:
    // Objeto do sensor IMU
    BMI088 imu;

    // Variáveis para o viés dos giroscópios
    float p_bias;
    float q_bias;
    float r_bias;
};

#endif
