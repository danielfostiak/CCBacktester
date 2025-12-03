#pragma once
#include <vector>
#include "Trade.h"

using Time = time_t;
using Amount = double;
using Volume = double;

struct Bar {
    Ticker ticker{};
    Time timestamp{};
    Amount ask{};
    Amount bid{};
    Volume askVolume{};
    Volume bidVolume{};
};

using Bars = std::vector<Bar>;