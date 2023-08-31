#ifndef Q3_H
#define Q3_H

#include <string>
#include <queue>
#include <fstream>
#include <istream>
#include <regex>

namespace q3 {

    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    struct cmp {
        bool operator()(const Flight& f1, const Flight& f2) {
            return f1.duration + f1.connection_times + f1.price * 3 >
                   f2.duration + f2.connection_times + f2.price * 3;
        }
    };

    inline size_t convTime(const std::string& t) {
        size_t hp = t.find('h');
        size_t mp = t.find('m');
        size_t hour, minute;
        if(hp != std::string::npos) {
            if(mp != std::string::npos and hp < mp) {
                hour = std::stoi(t.substr(0, hp));
                minute = std::stoi(t.substr(hp + 1, mp - hp - 1));
                return hour * 60 + minute;
            }
            hour = std::stoi(t.substr(0, hp));
            minute = 0;
        }
        return hour * 60 + minute;
    }

    inline std::priority_queue<Flight, std::vector<Flight>, cmp> gather_flights(const std::string& f) {
        std::priority_queue<Flight, std::vector<Flight>, cmp> flights;
        std::ifstream file(f);
        std::string line;
        while (std::getline(file, line)) {
            std::regex pattern(":(.*?)(?:\\s-|$)");

            auto start_ = std::sregex_iterator(line.begin(), line.end(), pattern);
            auto end_ = std::sregex_iterator();
            std::vector<std::string> extracted;
            for(std::sregex_iterator i = start_; i != end_; i++) {
                const std::smatch& match = *i;
                extracted.push_back(match.str(1));
            }

            size_t dur = convTime(extracted[1]);
            size_t connection = std::stoi(extracted[2]);
            std::istringstream tmp(extracted[3]);
            std::string cur;
            size_t tot = 0;
            while (std::getline(tmp, cur, ',')) {
                tot += convTime(cur);
            }
            size_t price_ = std::stoi(extracted[4]);

            flights.push({extracted[0], dur, connection, tot, price_});
        }
        return flights;
    }
}


#endif //Q3_H