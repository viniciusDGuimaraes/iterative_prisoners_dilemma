#include "base_strategy.h"

class GrudgeForgiving : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter > 0 && !their_previous_state)
        {
            hold_grudge = true;
        }

        if (their_previous_state)
        {
            their_collab_count += 1;
        }

        if (hold_grudge && their_collab_count == 2)
        {
            hold_grudge = false;
            their_collab_count = 0;
        }

        return !hold_grudge;
    }

private:
    bool hold_grudge=false;
    int their_collab_count = 0;
};