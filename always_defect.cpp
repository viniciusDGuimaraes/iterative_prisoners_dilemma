#include "base_strategy.h"

class AlwaysDefect : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        return false;
    }
};
