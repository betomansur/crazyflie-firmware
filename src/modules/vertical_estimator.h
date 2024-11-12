#ifndef vertical_estimator_h
#define vertical_estimator_h


#include "mbed.h"
#include "crazyflie.h"

class VerticalEstimator {
public:
  VerticalEstimator();
  void init();
  void predict(float f_t);
  void correct(float phi, float theta);
  float z, w;

private:
  VL53L1X range;
};

#endif