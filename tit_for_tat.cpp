#include "base_strategy.h"

class TitForTat : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter == 0) return true;

        return their_previous_state;
    }
};