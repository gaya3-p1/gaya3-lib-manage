#include "Utils.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <atomic>
#include <fstream>
#include <string>
#include <algorithm>

namespace Utils {

    static int loadMaxCounter(const std::string& prefix) {
        int maxVal = 0;
        for (const auto& path : {"data/transactions.csv", "data/history.csv"}) {
            std::ifstream f(path);
            if (!f.is_open()) continue;
            std::string line;
            while (std::getline(f, line)) {
                if (line.size() < prefix.size()) continue;
                if (line.substr(0, prefix.size()) == prefix) {
                    try {
                        int v = std::stoi(line.substr(prefix.size()));
                        if (v > maxVal) maxVal = v;
                    } catch (...) {}
                }
            }
        }
        return maxVal;
    }

    std::string generateID(const std::string& prefix) {
        static std::atomic<int> counter{-1};
        if (counter.load() == -1) {
            int seed = loadMaxCounter(prefix);
            counter.store(seed);
        }
        std::stringstream ss;
        ss << prefix << std::setw(6) << std::setfill('0') << ++counter;
        return ss.str();
    }

    std::string getDate() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d");
        return ss.str();
    }

    std::string addDays(const std::string& dateStr, int days) {
        std::tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        tm.tm_mday += days;
        std::mktime(&tm);
        std::ostringstream out;
        out << std::put_time(&tm, "%Y-%m-%d");
        return out.str();
    }

    int daysBetween(const std::string& from, const std::string& to) {
        std::tm tmFrom = {}, tmTo = {};
        std::istringstream ss1(from), ss2(to);
        ss1 >> std::get_time(&tmFrom, "%Y-%m-%d");
        ss2 >> std::get_time(&tmTo, "%Y-%m-%d");
        std::time_t t1 = std::mktime(&tmFrom);
        std::time_t t2 = std::mktime(&tmTo);
        return static_cast<int>((t2 - t1) / 86400);
    }

    bool validateInput(const std::string& input) {
        return !input.empty();
    }
}