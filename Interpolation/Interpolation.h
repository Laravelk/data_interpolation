#ifndef MATH_INTERPOLATION_H
#define MATH_INTERPOLATION_H

// Created by Иван Морозов on 2020-07-06.

#include <vector>

class Interpolation {
public:
    /* TODO: move to private */
    Interpolation() {}

    /*
     * x: vector of x values
     * y: vector of y values
     * z: vector of z values
     * f: function with two arguments
     * [x, y, z]
     * f = f(x,y)
     * */
    void cubicInterpolation(std::vector<double> x, std::vector<double> y,
            std::vector<double> z, double f(double x, double y));
private:
    /* EPS */
    constexpr static const double EPS = 0.00000001f;
};

#endif //MATH_INTERPOLATION_H
