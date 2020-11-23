#include "../util.h"
#include <iostream>
#include "GPIO.h"

using namespace exploringBB;

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

    GPIO gpio(49);
    gpio.setDirection(OUTPUT);
    gpio.setValue(GPIO_VALUE(value));

    return 0;
}
