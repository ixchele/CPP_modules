#include <iostream>
#include <ctime>

int main() {

    struct tm datetime = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL}; // Initialize all fields to zero
    datetime.tm_year = 2001 - 1900; // Year since 1900
    datetime.tm_mon = 1;           // 11 = December
    datetime.tm_mday = 30;          // 17th

    time_t timestamp = mktime(&datetime);

    if (timestamp != -1) {
        std::cout << "Timestamp: " << timestamp << std::endl;
        std::cout << "Date: " << ctime(&timestamp);
    } else {
        std::cout << "Error: Could not calculate time." << std::endl;
    }

    return 0;
}
