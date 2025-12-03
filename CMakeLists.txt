cmake_minimum_required(VERSION 4.0)
project(backtesterlocal)

set(CMAKE_CXX_STANDARD 20)

add_executable(backtesterlocal src/main.cpp
        src/Portfolio.h
        src/Backtester.h
        src/Trade.h
        src/Strategy.h
        src/IO/DataReader.h
        src/Bar.h
        src/IO/DataReader.cpp)
