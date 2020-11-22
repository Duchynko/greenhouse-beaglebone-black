#include "SG90.h"

int main(int argc, char const *argv[])
{
    string arg = argv[0];

    if (!arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit))
    {
        unsigned int angle = stoi(arg);

        if (angle < 0 || angle > 180)
        {
            auto servo = exploringBB::SG90("P9_23");
            servo.rotate(angle);
        }
    }
    return 0;
}
