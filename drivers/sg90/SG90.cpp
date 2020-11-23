#include "SG90.h"
#include <iostream>

namespace exploringBB
{
    SG90::SG90(string pinName) : PWM(pinName)
    {
        setPeriod(DEFAULT_PERIOD);
        setDutyCycle((unsigned int)MIN_PULSE_WIDTH);
        run();
    }

    void SG90::rotate(float angle)
    {
	    unsigned int dutyCycle = angleToDutyCycle(angle);
	    std::cout << "Servo duty cycle: " << dutyCycle << std::endl;
        setDutyCycle(dutyCycle);
    }

    unsigned int SG90::angleToDutyCycle(float angle)
    {
        unsigned int percentage = (angle * 100) / 180;
        unsigned int pulseWidth = (percentage * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 100) + MIN_PULSE_WIDTH;
        double dutyCycleRatio = (double)pulseWidth / DEFAULT_PERIOD;
	    return dutyCycleRatio * DEFAULT_PERIOD;
    }

    SG90::~SG90() {}
} // namespace exploringBB
