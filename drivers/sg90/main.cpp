#include "SG90.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    int angle;
    try {
        angle = std::atoi(argv[1]);
        if (angle < 0 || angle > 180) {
            throw 1;
        }
    } catch (...){
        std::cout << "Couldn't parse the argument. Angle must be in a range between 0 to 180." << std::endl;
        exit(1);
    }

    auto servo = exploringBB::SG90("pwm-1:1");
    servo.rotate(angle);
    return 0;
}
