#include <iostream>
#include <iomanip>
#include "IO/DataReader.h"

int main() {
    // chatgpt written test code to see if DataReader works, it does. But slow ~ 30 secs on my machine...
    // would be good if someone could reimplement DataReader::readData to be faster, currently it is just AI slop.
    try {
        DataReader reader{"../data/IVE_tickbidask.txt"};   // put your actual file name here
        Bars bars = reader.readData();

        std::cout << "Loaded " << bars.size() << " bars\n\n";

        // Print first 5 bars (or fewer if file is small)
        const size_t n = std::min<size_t>(5, bars.size());

        for (size_t i = 0; i < n; ++i) {
            const Bar& b = bars[i];

            std::tm* tm = std::localtime(&b.timestamp);

            std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S")
                      << " | O=" << b.open
                      << " H=" << b.high
                      << " L=" << b.low
                      << " C=" << b.close
                      << " V=" << b.volume
                      << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}