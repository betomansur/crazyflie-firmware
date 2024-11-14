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
    // Set initial references
    float z_r = 0.0;  // Initial reference
    float x_r = 0.0;
    float y_r = 0.0;
    float psi_r = 0.0;

    // State variables for trajectory
    enum State { TAKEOFF, HOVER, LAND } state = TAKEOFF;
    Timer timer;

    // Initialize estimators objects
    att_est.init();
    ver_est.init();
    hor_est.init();

    // Initialize interrupts
    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt_range);

    // Arm motors and run controller while stable
    mixer.arm();
    timer.start();

    while (abs(att_est.phi) <= pi / 4.0 && abs(att_est.theta) <= pi / 4.0 && abs(att_est.p) <= 4.0 * pi &&
           abs(att_est.q) <= 4.0 * pi && abs(att_est.r) <= 4.0 * pi)
    {
        if (flag)
        {
            flag = false;

            // Estimate attitude
            att_est.estimate();

            // Predict and correct vertical estimation
            ver_est.predict(ver_cont.f_t);
            if (flag_range)
            {
                flag_range = false;
                ver_est.correct(att_est.phi, att_est.theta);
            }

            // Predict and correct horizontal estimation
            hor_est.predict(att_est.phi, att_est.theta);
            if (ver_est.z >= 0.05)
            {
                hor_est.correct(att_est.phi, att_est.theta, att_est.p, att_est.q, ver_est.z);
                hor_cont.control(x_r, y_r, hor_est.x, hor_est.y, hor_est.u, hor_est.v);
            }

            // Control vertical position
            ver_cont.control(z_r, ver_est.z, ver_est.w);

            // Control attitude
            att_cont.control(hor_cont.phi_r, hor_cont.theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);

            // Actuate motors
            mixer.actuate(ver_cont.f_t / (cos(att_est.phi) * cos(att_est.theta)), att_cont.tau_phi, att_cont.tau_theta, att_cont.tau_psi);

            // Manage trajectory states
            switch (state)
            {
                case TAKEOFF:
                    z_r = 2.0;  // Target altitude for takeoff (increased to 2 meters)
                    if (ver_est.z >= 1.95)  // Close to target altitude
                    {
                        state = HOVER;
                        timer.reset();
                    }
                    break;

                case HOVER:
                    z_r = 2.0;  // Maintain hover altitude
                    if (timer.read() >= 10.0)  // Hover for 10 seconds (increased time)
                    {
                        state = LAND;
                    }
                    break;

                case LAND:
                    z_r = 0.0;  // Target altitude for landing
                    if (ver_est.z <= 0.05)  // Close to ground
                    {
                        mixer.disarm();
                        while (true);  // End program
                    }
                    break;
            }
        }
    }

    // Disarm motors and end program in case of instability
    mixer.disarm();
    while (true);
}
