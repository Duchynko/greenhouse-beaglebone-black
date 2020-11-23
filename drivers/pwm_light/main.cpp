#include "PWM.h"

int main(int argc, char const *argv[])
{
    unsigned int value = atoi(argv[1]);
    auto pwm = exploringBB::PWM("pwm-1:0");
    pwm.setDutyCycle((float)value);
    return 0;
}
