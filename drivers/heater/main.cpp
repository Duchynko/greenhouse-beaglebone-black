#include "../util.h"
#include <iostream>
#include "GPIO.h"

using namespace exploringBB;

int main(int argc, char const *argv[])
{
    short value = std::atoi(argv[1]);
    GPIO gpio(49);
    gpio.setDirection(OUTPUT);

    if (value == 1)
    {
        gpio.setValue(HIGH);
    }
    else
    {
        gpio.setValue(LOW);
    }
    return 0;
}
