#pragma once

enum class Ticker {
    IVE,
    PLTR,
    NVDA,
    AAPL,
    MAX_TICKERS,
};

enum class Side {
    BUY,
    SELL,
};

struct Trade {
    Ticker ticker{};
    Side side{};
    long amount{};
};