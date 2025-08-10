#include "base_strategy.h"
#include <cstdlib>

class Groffman : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter == 0) return true;

        if (my_previous_state != their_previous_state)
        {
            if (std::rand() % 7 >= 2)
            {
                return false;
            }
        }

        return true;
    }
};