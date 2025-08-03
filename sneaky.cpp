#include "base_strategy.h"
#include <cstdlib>

class Sneaky : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter == 0)
        {
            return true;
        }

        int random_num = std::rand() % 10;
        if (random_num < 1)
        {
            return false;
        }

        return their_previous_state;
    }
};