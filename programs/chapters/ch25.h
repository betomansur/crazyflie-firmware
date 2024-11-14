#include "mbed.h"
#include "crazyflie.h"

// Crazyflie controller objects
Mixer mixer;
AttitudeEstimator att_est;
AttitudeController att_cont;
VerticalEstimator ver_est;
VerticalController ver_cont;
HorizontalEstimator hor_est;
HorizontalController hor_cont;

// Ticker objects
Ticker tic, tic_range;

// Interrupt flag and counter variables
bool flag, flag_range;

// Callback functions
void callback() { flag = true; }
void callback_range() { flag_range = true; }

// Main program
int main()
{
    // Set references
    float z_r = 0.5;
    float x_r = 0.0;
    float y_r = 0.0;
    float psi_r = 0.0;

    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    hor_est.init();

    // Initialize interrupts
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range);

    // Arm motors and run controller while stable
    mixer.arm();
    while (abs(att_est.phi) <= pi / 4.0 && abs(att_est.theta) <= pi / 4.0 && abs(att_est.p) < 4 * pi &&
           abs(att_est.q) < 4 * pi && abs(att_est.r) < 4 * pi)
    {
        if (flag)
        {
            flag = false;

            // Estimate attitude
            att_est.estimate();

            // Control attitude
            att_cont.control(att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r, phi_r, theta_r, psi_r);

            // Actuate motors
            mixer.actuate(att_cont.omega_1, att_cont.omega_2, att_cont.omega_3, att_cont.omega_4);
        }
        if (flag_range)
        {
            flag_range = false;

            // Estimate vertical and horizontal positions
            ver_est.estimate();
            hor_est.estimate();
        }
    }

    // Disarm motors
    mixer.disarm();
    while (true);
}
