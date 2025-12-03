#pragma once
#include <vector>
#include "Bar.h"

class CSVReader {
    std::string m_file_name{};

public:
    explicit CSVReader(std::string_view file_name) : m_file_name{file_name} {}

    static std::vector<Bar> readCSV() {
        return {};
    }
};
