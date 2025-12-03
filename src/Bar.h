#pragma once
#include <vector>
#include "Trade.h"

using TimePoint = std::time_t;
using Price     = double;
using Volume    = double;

struct Bar {
    Ticker   ticker{Ticker::IVE};
    TimePoint timestamp{};
    Price    open{};
    Price    high{};
    Price    low{};
    Price    close{};
    Volume   volume{};
};

using Bars = std::vector<Bar>;