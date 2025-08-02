#include <memory>
#include <stdlib.h>
#include "strategy_listing.h"

class StrategyFactory
{
public:
    std::unique_ptr<BaseStrategy> create(const char* strategy_name)
    {
        if (strategy_name == "AlwaysCollab") return std::make_unique<AlwaysCollab>();
        if (strategy_name == "AlwaysDefect") return std::make_unique<AlwaysDefect>();
        if (strategy_name == "TitForTat") return std::make_unique<TitForTat>();
        
        return nullptr;
    }

    StrategyFactory() = default;
};