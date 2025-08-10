#include "base_strategy.h"

class Grudge : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter >= 10 && !their_previous_state)
        {
            hold_grudge = true;
        }

        return !hold_grudge;
    }

private:
    bool hold_grudge=false;
};