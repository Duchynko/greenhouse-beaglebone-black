#include "SG90.h"

namespace exploringBB
{
    SG90::SG90(string pinName) : PWM(pinName)
    {
        setPeriod(DEFAULT_PERIOD);
        setDutyCycle((unsigned int)MIN_DUTY_CYCLE);
        setPolarity(PWM::ACTIVE_LOW);
        run();
    }

    void SG90::rotate(float angle)
    {
        unsigned int milliseconds = angleToMilliseconds(angle);
        setDutyCycle(milliseconds * 1000000);
    }

    unsigned int SG90::angleToMilliseconds(float angle)
    {
        unsigned int percentage = (angle * 100) / 180;
        float range = MAX_DUTY_CYCLE - MIN_DUTY_CYCLE;
        return ((percentage * range) / 100) + MIN_DUTY_CYCLE;
    }

    SG90::~SG90() {}
} // namespace exploringBB