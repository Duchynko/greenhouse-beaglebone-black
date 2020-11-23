#include "../util.h"
#include <iostream>
#include "GPIO.h"

#define GPIO_PATH "/sys/class/gpio/gpio49/"
#define VALUE "value"

int main(int argc, char const *argv[])
{
    short value = std::atoi(argv[1]);
    auto gpio = exploringBB::GPIO(49);
    gpio.setDirection(exploringBB::GPIO_DIRECTION::OUTPUT);

    if (value == 1)
    {
        gpio.setValue(exploringBB::GPIO_VALUE::HIGH);
    }
    else
    {
        gpio.setValue(exploringBB::GPIO_VALUE::LOW);
    }
    return 0;
}
