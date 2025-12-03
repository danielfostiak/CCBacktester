#include "DataReader.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

#include <iomanip>
#include <iostream>

Bars DataReader::readData() const {
    Bars bars{};
    bars.reserve(1'000'000);   // tweak or remove; avoids a ton of reallocs

    std::ifstream file(m_file_name);
    if (!file) {
        throw std::runtime_error("Failed to open data file: " + m_file_name);
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        // Skip header line if present (first line non-digit)
        if (firstLine) {
            firstLine = false;
            if (!std::isdigit(static_cast<unsigned char>(line[0]))) {
                continue;
            }
        }

        // We expect: "MM/DD/YYYY,HH:MM:SS,p1,p2,p3,vol"
        if (line.size() < 20) {
            continue; // too short to be valid
        }

        // ---- Parse date & time directly from characters ----
        // Format: 09/28/2009,09:30:00,...
        // Indices: 0 1  /  3 4  /  6 7 8 9 , 11 12 : 14 15 : 17 18

        auto to_int2 = [](char a, char b) -> int {
            return (a - '0') * 10 + (b - '0');
        };

        int month = to_int2(line[0], line[1]);
        int day   = to_int2(line[3], line[4]);
        int year  = (line[6] - '0') * 1000
                  + (line[7] - '0') * 100
                  + (line[8] - '0') * 10
                  + (line[9] - '0');

        int hour   = to_int2(line[11], line[12]);
        int minute = to_int2(line[14], line[15]);
        int second = to_int2(line[17], line[18]);

        std::tm tm{};
        tm.tm_year = year - 1900;
        tm.tm_mon  = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min  = minute;
        tm.tm_sec  = second;
        tm.tm_isdst = -1;

        std::time_t ts = std::mktime(&tm);

        // ---- Parse numeric fields p1, p2, p3, vol ----
        // Find second comma (after time)
        std::size_t c1 = line.find(',', 0);
        if (c1 == std::string::npos) continue;
        std::size_t c2 = line.find(',', c1 + 1);
        if (c2 == std::string::npos) continue;

        const char* p   = line.c_str() + c2 + 1; // start of first price
        char* endp      = nullptr;

        auto next_double = [&](double& out) -> bool {
            // skip leading whitespace
            while (*p == ' ' || *p == '\t')
                ++p;

            out = std::strtod(p, &endp);
            if (p == endp) {
                return false; // no conversion
            }

            // Move past the comma if present
            if (*endp == ',') {
                p = endp + 1;
            } else {
                p = endp;
            }

            return true;
        };

        double p1, p2, p3, vol;
        if (!next_double(p1)) continue;
        if (!next_double(p2)) continue;
        if (!next_double(p3)) continue;
        if (!next_double(vol)) continue;

        Bar bar{};
        bar.ticker    = Ticker::IVE;  // as you already had
        bar.timestamp = ts;
        bar.open      = p1;
        bar.high      = p2;
        bar.low       = p3;
        bar.close     = p3;   // or whatever mapping you intend
        bar.volume    = vol;

        bars.emplace_back(bar);
    }

    return bars;
}
