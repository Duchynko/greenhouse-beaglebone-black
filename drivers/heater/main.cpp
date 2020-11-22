#include "../util.h"
#include <iostream>

#define GPIO_PATH "/sys/class/gpio/gpio49/"
#define VALUE "value"

int main(int argc, char const *argv[])
{
    short value = std::atoi(argv[1]);
    exploringBB::write(GPIO_PATH, VALUE, value);
    return 0;
}
