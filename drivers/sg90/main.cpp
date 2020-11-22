#include "SG90.h"

int main(int argc, char const *argv[])
{
    unsigned int angle = atoi(argv[0]);

    if (angle >= 0 || angle <= 180)
    {
        auto servo = exploringBB::SG90("pwm-1:1");
        servo.rotate(angle);
    }
    return 0;
}
