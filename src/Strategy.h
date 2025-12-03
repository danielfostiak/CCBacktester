#pragma once
#include <functional>
#include "Trade.h"
#include "Bar.h"

using OnBarFunc = std::function<Trade(Bar)>;

Trade exampleStrategy(Bar bar) {
    // example strategy of just buy nothing
    return Trade {Ticker::PLTR, Side::BUY, 0};
}