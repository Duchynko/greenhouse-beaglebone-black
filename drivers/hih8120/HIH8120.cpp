#include "HIH8120.h"
#include <iostream> // cout
#include <unistd.h> // usleep
#include <exception>

namespace exploringBB
{

#define HUMIDITY_MAX_COUNT 16382
#define HUMIDITY_MIN_COUNT 0
#define TEMPERATURE_MAX_COUNT 16382
#define TEMPERATURE_MIN_COUNT 0
#define NO_READ -99

    /**
     * Method to combine two 8-bit registers into a single short, which is 16-bits 
     * on the BBB. It shifts the MSB 8-bits to the left and then ORs the result 
     * with the LSB.
     * 
     * @param msb an unsigned character that contains the most significant byte
     * @param lsb an unsigned character that contains the least significant byte
     */
    // short HIH8120::combineRegisters(unsigned char msb, unsigned char lsb)
    // {
    //     //shift the MSB left by 8 bits and OR with LSB
    //     return ((short)msb << 8) | (short)lsb;
    // }

    short HIH8120::wakeUp()
    {
        unsigned char x = 0x00;
        short result = this->write(x);
        usleep(30000);
        return result;
    }

    bool HIH8120::isValidOutput(short output, short min_value, short max_value)
    {
        return !(output < min_value || output > max_value);
    }

    /**
     * Method to convert the digital output to humidity percentage. The output of 
     * the device is simply a 14 bit number representing between 0%RH and 100%RH.
     * The maximum humidity, 100%RH equals to 2^14 - 2 counts (TEMPERATURE_MAX_COUNT).
     * 
     * @param output A 14 bit digital output from the sensor
     */
    double HIH8120::calculateHumidity(short output)
    {
        if (!isValidOutput(output, HUMIDITY_MIN_COUNT, HUMIDITY_MAX_COUNT))
        {
            std::cout << "Humidity output " << output << " is out of range." << std::endl;
            throw "Out of range";
        }

        return output / (double)HUMIDITY_MAX_COUNT * 100.0;
    }

    /**
     * Method to convert the digital output to temperature in celsius. The output 
     * of the device is simply a 14 bit number representing between -40 and 120°C.
     * The maximum temperature, 120°C equals to 2^14 - 2 counts (HUMIDITY_MAX_COUNT).
     * 
     * @param output A 14 bit digital output from the sensor
     */
    double HIH8120::calculateTemperature(short output)
    {
        if (!isValidOutput(output, TEMPERATURE_MIN_COUNT, TEMPERATURE_MAX_COUNT))
        {
            std::cout << "Temperature output " << output << " is out of range." << std::endl;
            throw "Out of range";
        }

        return output / (double)TEMPERATURE_MAX_COUNT * 165 - 40;
    }

    /**
     * The constructor for the HIH8120 sensor object. It passes the bus number and 
     * the device address (which is 0x53 by default) to the constructor of I2CDevice. 
     * All of the states are initialized and the registers are updated.
     * 
     * @param I2CBus The bus number that the HIH8120 device is on - typically 0 or 1
     * @param I2CAddress The address of the HIH8120 device (default 0x27, but can be altered)
     */
    HIH8120::HIH8120(unsigned int I2CBus, unsigned int I2CAddress) : I2CDevice(I2CBus, I2CAddress)
    {
        this->I2CAddress = I2CAddress;
        this->I2CBus = I2CBus;
        this->humidity = NO_READ;
        this->temperature = NO_READ;
    }

    /**
     * This method  will reads the sensor's output and pass them to the combineRegisters() method to be processed.
     * @return 0 if the registers are successfully read and -1 if the device ID is incorrect.
     */
    int HIH8120::readSensorState()
    {
        this->wakeUp();

        this->registers = this->readDevice(BUFFER_SIZE);
        short rawHumidity = ((short)this->registers[0] << 8) | (short)this->registers[1];
        short rawTemperature = ((short)this->registers[2] << 8) | (short)this->registers[3];
        // TODO: Refactor this
        rawTemperature = rawTemperature >> 2;

        this->humidity = this->calculateHumidity(rawHumidity);
        this->temperature = this->calculateTemperature(rawTemperature);
        return 0;
    }

    HIH8120::~HIH8120() {}

} /* namespace exploringBB */