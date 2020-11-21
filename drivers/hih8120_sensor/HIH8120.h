#include "I2CDevice.h"

#define BUFFER_SIZE 4

namespace exploringBB
{
    /**
     * @class HIH8120
     * @brief Specific class for the HIH8120 Humidity & Temperature sensor that is a child of 
     * the I2CDevice class. Protected inheritance means that the public I2CDevice methods are 
     * not publicly accessible by an object of the HIH8120 class.
     */
    class HIH8120 : protected I2CDevice
    {

    private:
        unsigned int I2CBus, I2CAddress;
        unsigned char *registers;
        double humidity, temperature;
        short combineRegisters(unsigned char msb, unsigned char lsb);
        double calculateHumidity(short output);
        double calculateTemperature(short output);
        bool isValidOutput(short output, short min_value, short max_value);
        virtual short wakeUp();

    public:
        HIH8120(unsigned int I2CBus, unsigned int I2CAddress = 0x27);
        virtual int readSensorState();
        virtual double getHumidity() { return humidity; }
        virtual double getTemperature() { return temperature; }
        virtual ~HIH8120();
    };

} /* namespace exploringBB */
