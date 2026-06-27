#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    std::string generateID(const std::string& prefix = "TXN");
    std::string getDate();
    std::string addDays(const std::string& dateStr, int days);
    int daysBetween(const std::string& from, const std::string& to);
    bool validateInput(const std::string& input);
}

#endif