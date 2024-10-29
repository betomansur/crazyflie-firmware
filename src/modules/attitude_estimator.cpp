#include "attitude_estimator.h"

// Construtor da classe
AttitudeEstimator::AttitudeEstimator() : imu(IMU_SDA, IMU_SCL) {
    // Inicializa os ângulos de Euler e velocidades angulares
    phi = 0.0;
    theta = 0.0;
    psi = 0.0;
    p = 0.0;
    q = 0.0;
    r = 0.0;
}

// Inicializa a classe
void AttitudeEstimator::init() {
    imu.init();

    float soma_x = 0.0; // Inicializa a soma para o cálculo do viés
    float soma_y = 0.0;
    float soma_z = 0.0;

    // Coleta dados para calcular o viés
    for (int i = 0; i < 500; i++) {
        imu.read();
        soma_x += imu.gx;
        soma_y += imu.gy;
        soma_z += imu.gz;
        wait(dt);
    }

    // Calcula o viés médio
    p_bias = soma_x / 500.0;
    q_bias = soma_y / 500.0;
    r_bias = soma_z / 500.0;
}

// Estima ângulos de Euler (rad) e velocidades angulares (rad/s)
void AttitudeEstimator::estimate() {
    imu.read(); // Lê os dados do sensor IMU

    // Corrige as leituras do giroscópio
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;

    // Estimativas de ângulos de Euler usando o acelerômetro
    float phi_a = atan2(-imu.ay, -imu.az);
    float theta_a = atan2(imu.ax, -sqrt(imu.ay * imu.ay + imu.az * imu.az));

    // Estimativas de ângulos de Euler a partir do giroscópio
    float phi_g = phi + (p + sin(phi) * tan(theta) * q + cos(phi) * tan(theta) * r) * dt;
    float theta_g = theta + (cos(phi) * q - sin(phi) * r) * dt;
    float psi_g = psi + (sin(phi) / cos(theta) * q + cos(phi) / cos(theta) * r) * dt;

    // Filtro complementar para suavizar as estimativas
    phi = (1 - alpha) * phi_g + alpha * phi_a;
    theta = (1 - alpha) * theta_g + alpha * theta_a;
    psi = psi_g; // Atualiza psi diretamente
}
