#pragma once
#include "Portfolio.h"
#include "Strategy.h"
#include "Bar.h"

class Backtester {
    Portfolio m_portfolio{};
    OnBarFunc m_strategy{};
    Bars m_data{};

public:
    explicit Backtester(OnBarFunc strategy, const Bars& data)
    : m_strategy{strategy}, m_data{data} {}

    void backtest() {
        for (const Bar& bar: m_data) {
            m_portfolio.addTrade(m_strategy(bar));
        }
    }

    double evaluateStrategy() {
        // just tells you what the trades done are...
        return m_portfolio.trades();
    }
};
