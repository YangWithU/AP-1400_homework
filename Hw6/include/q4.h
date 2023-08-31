#ifndef Q4_H
#define Q4_H

#include <vector>

namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
    };

    struct Sensor {
        Vector2D pos{};
        double accuracy;
    };

    inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
        double acc_sum = 0;
        auto sum = [&acc_sum](Sensor& ss) { acc_sum += ss.accuracy; };
        std::for_each(sensors.begin(), sensors.end(), sum);

        std::vector<double> weight;
        auto deliver = [&weight, acc_sum](Sensor& ss) { weight.push_back(ss.accuracy / acc_sum); };
        std::for_each(sensors.begin(), sensors.end(), deliver);

        size_t i = 0;
        double x_sum = 0;
        auto x_calc = [&i, &x_sum, weight](Sensor& ss) { x_sum += weight[i] * ss.pos.x; i++; };
        std::for_each(sensors.begin(), sensors.end(), x_calc);

        i = 0;
        double y_sum = 0;
        auto y_calc = [&i, &y_sum, weight](Sensor& ss) { y_sum += weight[i] * ss.pos.y; i++; };
        std::for_each(sensors.begin(), sensors.end(), y_calc);

        return {x_sum, y_sum};
    }
}

#endif //Q4_H