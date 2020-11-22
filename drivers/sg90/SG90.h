#include "PWM.h"

#define DEFAULT_PERIOD 20000000 // 20ms (50hz)
#define MIN_DUTY_CYCLE 1000000  // 1ms
#define MAX_DUTY_CYCLE 5000000  // 5ms

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
        double angleToDutyCycle(float angle);
    };
} /* namespace exploringBB */
