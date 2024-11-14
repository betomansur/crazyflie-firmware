#include "horizontal_controller.h"

// Class constructor
HorizontalController::HorizontalController ()
{
    phi_r, theta_r = 0;
}

void HorizontalController::control (float x_r , float y_r , float x, float y, float u, float v)
{
    theta_r = (1.0/g)*control_siso(x_r, x, u, kp_hc, kd_hc);
    phi_r = (-1.0/g)*control_siso(y_r, y, v, kp_hc, kd_hc);
}

float HorizontalController::control_siso (float pos_r , float pos , float vel , float kp , float kd)
{
    return kp*(pos_r - pos) + kd*(0 - vel);
}