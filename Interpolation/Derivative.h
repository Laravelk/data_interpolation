#ifndef MATH_DERIVATIVE_H
#define MATH_DERIVATIVE_H
// Created by Иван Морозов on 2020-07-06.

#include <cmath>

#include <libInterpolate/Interpolate.hpp>

class Derivative {
public:
    /*
     * реализация для функций двух переменных
     * */

    /* derivative by any function with two argument */
    static double derivative_x(double x, double y, double f(double f_x, double f_y)) {
        return (f(x + EPS, y) - f(x - EPS, y)) / (2 * EPS);
    }

    static double derivative_y(double x, double y, double f(double x, double y)) {
        return (f(x, y + EPS) - f(x, y - EPS)) / (2 * EPS);
    }

    /* derivative by interpolator value */
    static double derivative_x(double x, double y,
                               _2D::BicubicInterpolator<double> interpolator) {
        return (interpolator(x + EPS, y) -
                interpolator(x - EPS, y)) / (2 * EPS);
    }

    static double derivative_y(double x, double y,
                               _2D::BicubicInterpolator<double> interpolator) {
        return (interpolator(x + EPS, y) -
                interpolator(x - EPS, y)) / (2 * EPS);
    }

    /* derivative by any function with two arguments */
    static double derivative_xx(double x, double y, double f(double f_x, double f_y)) {
        return (derivative_x(x + EPS, y, f) -
        derivative_x(x - EPS, y, f)) / (2 * EPS);
    }

    static double derivative_yy(double x, double y, double f(double x, double y)) {
        return (derivative_y(x, y + EPS, f) -
        derivative_y(x, y - EPS, f)) / (2 * EPS);
    }

    /* derivative by interpolation value */

    static double derivative_xx(double x, double y,
                                _2D::BicubicInterpolator<double> interpolator) {
        return (derivative_x(x + EPS, y, interpolator) -
                derivative_x(x - EPS, y, interpolator)) / (2 * EPS);
    }

    static double derivative_yy(double x, double y,
                                _2D::BicubicInterpolator<double> interpolator) {
        return (derivative_y(x, y + EPS, interpolator) -
                derivative_y(x, y - EPS, interpolator)) / (2 * EPS);
    }

private:
    /* EPS */
    constexpr static const double EPS = 0.00000001f;
};


#endif //MATH_DERIVATIVE_H
