#pragma once

#include <vector>
#include <string>



#include "../Bar.h"

class DataReader {
    std::string m_file_name{};

public:
    explicit DataReader(std::string_view file_name) : m_file_name{file_name} {
    }

    Bars readData() const;
};
