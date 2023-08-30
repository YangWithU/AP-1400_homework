#ifndef Q2_H
#define Q2_H

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::vector<Patient> read_file(std::string filename) {
        std::vector<Patient> res;
        std::ifstream file(filename);
        std::string hd_line;
        std::getline(file, hd_line); // read header line
        std::getline(file, hd_line);

        std::string name, surname;
        std::string age, smokes, area_q, alkhol;
        while (std::getline(file, hd_line)) {
            std::istringstream buffer(hd_line);
            std::getline(buffer, name, ',');
            std::getline(buffer, surname, ',');
            std::getline(buffer, age, ',');
            std::getline(buffer, smokes, ',');
            std::getline(buffer, area_q, ',');
            std::getline(buffer, alkhol, ',');
            size_t a1 = std::stoi(age), a2 = std::stoi(smokes);
            size_t a3 = std::stoi(area_q), a4 = std::stoi(alkhol);
            name += " ";
            res.push_back({name + surname, a1, a2, a3, a4});
        }

        file.close();
        return res;
    }

    inline void sort(std::vector<Patient>& res) {
        std::sort(res.begin(), res.end(), [](const Patient& p1, const Patient& p2) {
            return p1.age * 3 + p1.smokes * 5 + p1.area_q * 2 + p1.alkhol * 4 >
            p2.age * 3 + p2.smokes * 5 + p2.area_q * 2 + p2.alkhol * 4;
        });
    }
}

#endif //Q2_H