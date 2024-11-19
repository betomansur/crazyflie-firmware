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
Timer tim;
float t;
float ts = 4.0; //tempo de subida
float tv = 3.0; //tempo de voo
float td = 7.0; //tempo de descida
float h = 1.0; //m
float d = 2.0; //m

// Interrupt flag and counter variables
bool flag, flag_range;

// Callback functions
void callback() { flag = true; }
void callback_range() { flag_range = true; }

// Main program
int main() {
  // Set references
  float z_r = 0.0;
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
  tim.start();
  while (abs(att_est.phi) <= pi / 4.0 && abs(att_est.theta) <= pi / 4.0 && abs(att_est.p) <= 4.0 * pi && abs(att_est.q) <= 4.0 * pi && abs(att_est.r) <= 4.0 * pi) {
    if (flag) {
      t = tim.read();
      flag = false;
      att_est.estimate();
      ver_est.predict(ver_cont.f_t);

      if(t < ts) {
        z_r = (h/ts)*t;
        x_r = 0.0;
      }

      if(t >= ts && t < (ts+tv)) {
          z_r = h;
          x_r = (d/tv)*(t-ts);
          //x_r = 0.0;
      }

      if(t >= (ts+tv)) {
          z_r = (h/td)*(td+ts+tv-t);
          x_r = d;
          //x_r = 0.0;
      }
      if(t >= (ts+tv+td+0.5))
      {
          mixer.disarm();
      }

      if (flag_range) {
        flag_range = false;
        ver_est.correct(att_est.phi, att_est.theta);
      }

      hor_est.predict(att_est.phi, att_est.theta);
      if (ver_est.z >= 0.05) {
        hor_est.correct(att_est.phi, att_est.theta, att_est.p, att_est.q, ver_est.z);
        hor_cont.control(x_r, y_r, hor_est.x, hor_est.y, hor_est.u, hor_est.v);
      }

      ver_cont.control(z_r, ver_est.z, ver_est.w);
      att_cont.control(hor_cont.phi_r, hor_cont.theta_r, psi_r, att_est.phi, att_est.theta, att_est.psi, att_est.p, att_est.q, att_est.r);
      mixer.actuate(ver_cont.f_t / (cos(att_est.phi) * cos(att_est.theta)), att_cont.tau_phi, att_cont.tau_theta, att_cont.tau_psi);
    }
  }

  // Disarm motors and end program
  mixer.disarm();
  while (true);
}