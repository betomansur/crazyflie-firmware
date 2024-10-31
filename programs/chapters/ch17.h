#include "mbed.h"
#include "crazyflie.h"

// Objetos do controlador Crazyflie
Mixer mixer;
AttitudeEstimator att_est;
AttitudeController att_cont;

// Objetos Ticker
Ticker tic;

// Variáveis de interrupção e contadores
bool flag;

// Função de callback
void callback() { flag = true; }

// Programa principal
int main()
{
    // Definir referências
    float f_t = 0.5 * m * g;
    float phi_r = 0.0;
    float theta_r = 0.0;
    float psi_r = 0.0;

    // Inicializar objetos do estimador
    att_est.init();

    // Inicializar interrupções
    tic.attach(&callback, dt);

    // Armar motores e executar controlador enquanto estiver estável
    mixer.arm();
    while (abs(att_est.phi) <= pi / 4.0 && abs(att_est.theta) <= pi / 4.0 && abs(att_est.p) <= 4.0 * pi &&
           abs(att_est.q) <= 4.0 * pi && abs(att_est.r) <= 4.0 * pi)
    {
        if (flag)
        {
            flag = false;
            att_est.estimate();
            att_cont.control(phi_r, theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);
            mixer.actuate(f_t, 0.0, att_cont.tau_theta, 0.0);
        }
    }
    
    // Desarmar motores e finalizar programa
    mixer.disarm();
    while (true);
}