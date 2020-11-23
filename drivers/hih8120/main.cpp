/*
* The program loops through and reads output from the hih8120 sensor,
* outputing data after every read. The output of the sensor is in
* the following format:
*
* Humidity     (%): 40
* Temperature (°C): 22
* 
* Author: Jakub Duchon
* Date: 23.11.2020
*/

#include "HIH8120.h"
#include "I2CDevice.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // Representation of 1 second in microseconds
    unsigned int second = 1000000;

    while (true)
    {
        auto sensor = exploringBB::HIH8120(2, 0x27);
        sensor.readSensorState();
        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << "Humidity (%)      :" << sensor.getHumidity() << std::endl;
        std::cout << "Temperature (°C)  :" << sensor.getTemperature() << std::endl;
        usleep(second * 10);
    }
}
