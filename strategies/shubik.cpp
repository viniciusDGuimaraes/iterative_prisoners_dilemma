#include "base_strategy.h"

class Shubik : public BaseStrategy
{
public:
    bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) override
    {
        if (curr_iter == 0) return true;

        if (!their_previous_state && !in_defect_run)
        {
            their_defect_count += 1;
            in_defect_run = true;
        }

        if (in_defect_run)
        {
            if (defect_run_count < their_defect_count)
            {
                defect_run_count += 1;
                return false;
            }

            defect_run_count = 0;
            in_defect_run = false;
        }

        return true;
    }

private:
    int their_defect_count = 0;
    int defect_run_count = 0;
    bool in_defect_run = false;
};