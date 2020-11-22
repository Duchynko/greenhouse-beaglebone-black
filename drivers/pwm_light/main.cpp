#include "SG90.h"

int main(int argc, char const *argv[])
{
    unsigned int value = atoi(argv[1]);
    auto pwm = exploringBB::PWM("pwm-1:1");
    pwm.setDutyCycle(value);
    return 0;
}
