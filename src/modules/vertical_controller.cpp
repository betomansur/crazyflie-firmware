#include "vertical_controller.h"

VerticalController :: VerticalController ()
{
f_t = 0;
}

void VerticalController :: control ( float z_r , float z, float w)
{
f_t = m*(g+control_siso(z_r, z, w, kp_vc, kd_vc));
}

float VerticalController :: control_siso ( float pos_r , float pos , float vel , float kp ,float kd)
{
return kp * (pos_r - pos) + kd * (0 - vel);
}