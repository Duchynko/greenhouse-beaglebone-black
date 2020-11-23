#include "SG90.h"
#include <iostream>

namespace exploringBB
{
    SG90::SG90(string pinName) : PWM(pinName)
    {
        setPeriod(DEFAULT_PERIOD);
        setDutyCycle((unsigned int)MIN_DUTY_CYCLE);
        run();
    }

    void SG90::rotate(float angle)
    {
        double dutyCycle = angleToDutyCycle(angle);
        unsigned int dcInNs = dutyCycle * 1000000 * 10;
        std::cout << dcInNs << std::endl;
        setDutyCycle(dcInNs);
    }

    double SG90::angleToDutyCycle(float angle)
    {
        unsigned int percentage = (angle * 100) / 180;
        unsigned int pulseWidth = (percentage * (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / 100) + MIN_DUTY_CYCLE;
        std::cout << pulseWidth << " " << (double)pulseWidth / DEFAULT_PERIOD << std::endl;
        return (double)pulseWidth / DEFAULT_PERIOD;
    }

    SG90::~SG90() {}
} // namespace exploringBB
