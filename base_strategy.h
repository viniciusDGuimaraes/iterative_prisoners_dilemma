#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

class BaseStrategy
{
public:
    virtual bool get_answer(bool my_previous_state, bool their_previous_state, int my_score, int their_score, int curr_iter) = 0;
};

#endif