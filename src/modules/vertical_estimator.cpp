#include "vertical_estimator.h"

VerticalEstimator ::VerticalEstimator() : range(E_SDA, E_SCL) {
  z = 0;
  w = 0; 
}

void VerticalEstimator ::init() { range.init(); }

void VerticalEstimator ::predict(float f_t) {
  z += w*dt;
}

void VerticalEstimator ::correct(float phi, float theta) {
  range.read();
  if (range.d < 4.0) {
    float z_m = range.d * cos(phi) * cos(theta);
    w += l_1*dt_range*(z_m - z);
    z += l_2*dt_range*(z_m - z);
  }
}