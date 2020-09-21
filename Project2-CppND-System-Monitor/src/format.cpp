#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(int seconds) {
    std::time_t t(seconds);

    std::stringstream ss;
    ss << std::put_time(std::gmtime(&t), "%H:%M:%S");

    std::string result = ss.str();
    return result;
}