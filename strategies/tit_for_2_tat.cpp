#include "base_strategy.h"

class TitFor2Tat : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter == 0) return true;

        if (!their_previous_state)
        {
            defect_count += 1;
        }

        if (defect_count < 2)
        {
            return true;
        }

        if (their_previous_state)
        {
            defect_count = 0;
        }

        return their_previous_state;
    }

private:
    int defect_count = 0;
};