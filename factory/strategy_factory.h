#include <memory>
#include <stdlib.h>
#include "strategy_listing.h"

class StrategyFactory
{
public:
    std::unique_ptr<BaseStrategy> create(const std::string strategy_name)
    {
        if (strategy_name == "AlwaysCollab") return std::make_unique<AlwaysCollab>();
        if (strategy_name == "AlwaysDefect") return std::make_unique<AlwaysDefect>();
        if (strategy_name == "TitForTat") return std::make_unique<TitForTat>();
        if (strategy_name == "Grudge") return std::make_unique<Grudge>();
        if (strategy_name == "Sneaky") return std::make_unique<Sneaky>();
        if (strategy_name == "Random") return std::make_unique<Random>();

        
        return nullptr;
    }

    StrategyFactory() = default;
};