#pragma once
#include "Trade.h"
#include <vector>

class Portfolio {
    std::vector<Trade> m_trades{};
    double m_cash{ 0.0 };

public:
    Portfolio() = default;

    std::vector<Trade> trades() const { return m_trades; }

    void addTrade(Trade trade) { m_trades.push_back(trade); }

    double cash() const { return m_cash; }

    std::vector<Trade> trades() const { return m_trades; }
};