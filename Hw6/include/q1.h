#ifndef Q1_H
#define Q1_H

#include <functional>
#include <cmath>

namespace q1 {
    inline double dydx(std::function<double(double)>& func, double x, double epsilon = 1e-6) {
        double fx = func(x);
        double fx_plus_h = func(x + epsilon);
        double res = (fx_plus_h - fx) / epsilon;
        return res;
    }

    inline double gradient_descent(double start_, double step_, std::function<double(double)> func, int tot_step = 1e6) {
        double cur = start_;
        for(int i = 0; i < tot_step; i++) {
            double gradient = dydx(func, cur);
            cur -= step_ * gradient;
        }
        return cur;
    }

    template<typename T, class Func>
    inline double gradient_descent(T start_, T step_) {
        return gradient_descent(start_, step_, Func());
    }

}


#endif //Q1_H