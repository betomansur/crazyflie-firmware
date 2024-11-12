#ifndef VERTICAL_ESTIMATOR_H
#define VERTICAL_ESTIMATOR_H

#include "mbed.h"
#include "crazyflie.h"
#include "vl53l1x.h"

class VerticalEstimator {
public:
    // Class constructor
    VerticalEstimator();

    // Initialize the vertical estimator
    void init();

    // Predict vertical state (position and velocity)
    void predict(float dt);

    // Correct vertical state with sensor measurement
    void correct();

    // Estimated vertical position (z) and velocity (w)
    float z, w;

private:
    // Range sensor
    VL53L1X range;

    // Measurement state
    bool range_ready;
};

#endif // VERTICAL_ESTIMATOR_H
