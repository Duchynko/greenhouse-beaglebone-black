/*
* The program takes the `value` argument, validates it, and if the
* value is in the range from 0 to 100, it writes the value to the 
* specified PWM PIN.
* 
* Author: Jakub Duchon
* Date: 23.11.2020
*/

#include "../PWM.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    int value;
    try {
        value = std::atoi(argv[1]);
        if (value != 0 && value != 1) {
            throw 1;
        }
    } catch (...){
        std::cout << "Couldn't parse the argument. Value must be 1 or 0." << std::endl;
        exit(1);
    }

    auto pwm = exploringBB::PWM("pwm-1:0");
    pwm.setPeriod(20000000);
    pwm.setDutyCycle((float)value);
    return 0;
}
