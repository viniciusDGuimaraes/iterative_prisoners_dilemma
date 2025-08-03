#include "base_strategy.h"
#include <cstdlib>

class Random : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        int random_num = std::rand() % 2;
        if (random_num == 0)
        {
            return false;
        }

        return true;
    }
};