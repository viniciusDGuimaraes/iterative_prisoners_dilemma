#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <format>
#include "strategy_factory.h"


int main(int argc, char* argv[])
{
    const int max_iters = 10000;
    argv[0] = "AlwaysCollab";
    argv[0] = "TitForTat";
    argv[1] = "AlwaysDefect";
    argv[2] = "10";
    argv[3] = "3";
    argv[4] = "2";
    argv[5] = "1";
    argv[6] = "4";

    const char* strategy_1 = argv[0];
    const char* strategy_2 = argv[1];
    const int iterations = strtol(argv[2], NULL, 10);
    const int reward_payoff = strtol(argv[3], NULL, 10);
    const int punishment_payoff = strtol(argv[4], NULL, 10);
    const int sucker_payoff = strtol(argv[5], NULL, 10);
    const int temptation_payoff = strtol(argv[6], NULL, 10);

    if (iterations > max_iters)
    {
        // TODO improve error message
        //std::string iter_error_msg = std::format("Number of iterations {0} exceed allowed number of iterations {1}", iterations, max_iters);
        std::string iter_error_msg = "Number of iterations exceed max allowed number";
        return -1;
        //throw std::invalid_argument(iter_error_msg);
    }

    if (!(temptation_payoff > reward_payoff &&
          reward_payoff > punishment_payoff &&
          punishment_payoff > sucker_payoff &&
          (2 * reward_payoff) > (temptation_payoff + sucker_payoff)))
    {
        std::string rewards_error_msg = "Invalid values for rewards";
        return -1;
        //throw std::invalid_argument(rewards_error_msg);
    }

    std::unique_ptr<StrategyFactory> factory = std::make_unique<StrategyFactory>();
    std::unique_ptr<BaseStrategy> first_strategy = factory->create(strategy_1);
    std::unique_ptr<BaseStrategy> second_strategy = factory->create(strategy_2);

    // Init variables
    bool s1_answer = false;
    bool s2_answer = false;
    int s1_score = 0;
    int s2_score = 0;

    for (int iter = 0; iter < iterations; ++iter)
    {
        s1_answer = first_strategy->get_answer(s1_answer, s2_answer, s1_score, s2_score, iter);
        s2_answer = second_strategy->get_answer(s2_answer, s1_answer, s2_score, s1_score, iter);

        // One collaborated while the other defected
        if (s1_answer != s2_answer)
        {
            // Strategy 1 collaborated
            if (s1_answer)
            {
                s1_score += sucker_payoff;
                s2_score += temptation_payoff;
            }
            // Strategy 2 collaborated
            else
            {
                s2_score += sucker_payoff;
                s1_score += temptation_payoff;
            }
        }
        // Both chose the same action
        else
        {
            // Both collaborated
            if (s1_answer)
            {
                s1_score += reward_payoff;
                s2_score += reward_payoff;
            }
            // Both defected
            else
            {
                s1_score += punishment_payoff;
                s2_score += punishment_payoff;
            }
        }
    }

    printf("Score for first strategy: %i\n", s1_score);
    printf("Score for second strategy: %i\n", s2_score);

    return 0;
}