/*
* The program loops through and reads output from the ldr sensor,
* outputing data after every read.
* 
* Author: Jakub Duchon
* Date: 23.11.2020
*/

#include "../util.h"
#include <iostream>
#include <unistd.h>

#define GPIO_PATH "/sys/bus/iio/devices/iio:device0/"
#define VALUE "in_voltage0_raw"

int main(int argc, char const *argv[])
{
    while (true)
    {
        string value = exploringBB::read(GPIO_PATH, VALUE);
        std::cout << "Light intesnity read: " << value << std::endl;
        usleep(1000000 * 10);
    }
    return 0;
}
