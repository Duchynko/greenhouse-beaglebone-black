#include "SG90.h"

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
        unsigned int dutyCycle = angleToDutyCycle(angle);
        setDutyCycle(dutyCycle * 1000000);
    }

    double SG90::angleToDutyCycle(float angle)
    {
        unsigned int percentage = (angle * 100) / 180;
        unsigned int pulseWidth = (percentage * (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE) / 100) + MIN_DUTY_CYCLE;
        return (double)pulseWidth / DEFAULT_PERIOD;
    }

    SG90::~SG90() {}
} // namespace exploringBB