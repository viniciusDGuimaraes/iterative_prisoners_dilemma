#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <format>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "strategy_factory.h"


bool load_strategy_file(const std::string& filepath, std::vector<std::string>& strategies)
{
    std::ifstream input_file(filepath);

    if (!input_file.is_open())
    {
        printf("Failed to open file %s", filepath);
        return false;
    }

    std::string line;

    while (std::getline(input_file, line))
    {
        strategies.push_back(line);
    }

    return true;
}


int main(int argc, char* argv[])
{
    argv[0] = "/home/vinicius/Documents/iterative_prisoners_dilemma/strategies.txt";
    argv[1] = "200";

    std::vector<std::string> strategies;
    if (!load_strategy_file(argv[0], strategies))
    {
        printf("Failed to open file %s", argv[0]);
        return -1;
    }

    const int max_iters = 10000;
    const int iterations = strtol(argv[1], NULL, 10);
    const int reward_payoff = 3;
    const int punishment_payoff = 1;
    const int sucker_payoff = 0;
    const int temptation_payoff = 5;

    if (iterations > max_iters)
    {
        // TODO improve error message
        //std::string iter_error_msg = std::format("Number of iterations {0} exceed allowed number of iterations {1}", iterations, max_iters);
        std::string iter_error_msg = "Number of iterations exceed max allowed number";
        return -1;
        //throw std::invalid_argument(iter_error_msg);
    }

    std::unique_ptr<StrategyFactory> factory = std::make_unique<StrategyFactory>();
    std::unordered_map<std::string, int> strategies_scores;

    // Init score hashmap
    for (std::string strategy : strategies)
    {
        strategies_scores[strategy] = 0;
    }

    for (int i=0; i < strategies.size(); ++i)
    {
        for (int j=i; j < strategies.size(); ++j)
        {
            std::string strategy_1 = strategies[i];
            std::string strategy_2 = strategies[j];

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

            strategies_scores[strategy_1] += s1_score;
            strategies_scores[strategy_2] += s2_score;
        }
    }

    for (std::string strategy : strategies)
    {
        float avg_score = strategies_scores[strategy] / strategies.size();
        printf("Average score for strategy %s: %f\n", strategy.c_str(), avg_score);
    }

    return 0;
}