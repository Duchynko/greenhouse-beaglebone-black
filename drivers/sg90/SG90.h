#include "../PWM.h"

#define DEFAULT_PERIOD 20000000 // 20ms (50hz)
#define MIN_PULSE_WIDTH 500000  // 0.5ms
#define MAX_PULSE_WIDTH 2500000  // 2.5ms

namespace exploringBB
{
    /**
     * @class HIH8120
     * @brief Specific class for the HIH8120 Humidity & Temperature sensor that is a child of 
     * the I2CDevice class. Protected inheritance means that the public I2CDevice methods are 
     * not publicly accessible by an object of the HIH8120 class.
     */
    class SG90 : protected PWM
    {
    public:
        SG90(string pinName);
        virtual void rotate(float angle);
        virtual ~SG90();

    private:
        unsigned int angleToDutyCycle(float angle);
    };
} /* namespace exploringBB */
