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

    static std::vector<double> get_steps(std::vector<double> x) {
        std::vector<double> steps;
        steps.reserve(x.size() - 1);
        for (unsigned long i = 0; i < x.size() - 1; i++) {
            steps.push_back(abs(x[i + 1] - x[i]));
        }
        return steps;
    }

    /* derivative with steps */
    static std::vector<double> derivative_with_steps(std::vector<double> x, std::vector<double> steps,
            _2D::BicubicInterpolator<double> interpolator) {
        std::vector<double> derivative;
        const double delta = 0.001f;
        for (auto v_x : x) {
            double dir = interpolator(v_x, 0);
            derivative.push_back(dir);
        }
        return derivative;
    }

    /* derivative vector */
    static std::vector<double> derivative_xx_const_y(std::vector<double> x, double y, _2D::BicubicInterpolator<double> interpolator) {
        std::vector<double> derivative;
        for (auto v_x : x) {
            double dir = (interpolator(v_x + 20.0f / 41.0f, y) - 2 * interpolator(v_x, y) + interpolator(v_x - 20.0f / 41.0f, y)) / (20.0f / 41.0f * 20.0f / 41.0f);
            std::cerr << v_x << ": " << dir << std::endl;
            derivative.push_back(dir);
        }
        return derivative;
    }

    static std::vector<double> derivative_xx_const_y(std::vector<double> x, double y, double f(double f_x, double f_y)) {
        std::vector<double> derivative;
        for (auto v_x : x) {
            double dir = (f(v_x + 20.0f / 41.0f, y) - 2 * f(v_x, y) + f(v_x - 20.0f / 41.0f, y)) / (20.0f / 41.0f * 20.0f / 41.0f);
            std::cerr << v_x << ": " << dir << std::endl;
            derivative.push_back(dir);
        }
        return derivative;
    }

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

    /* second variant for derivative */
    static double derivative_xxs(double x, double y, _2D::BicubicInterpolator<double> interpolator, double grid_step) {
        //double u0 = x - EPS;
        //double u1 = x;
        //double u2 = x + EPS;
        //return (interpolator(u0, y) - 2 * interpolator(u1, y) + interpolator(u2, y)) / (grid_step * grid_step);
        return (interpolator(x + EPS, y) - interpolator(x - EPS, y)) / (grid_step * grid_step);
        //return (u0 - 2 * u1 + u2) / (grid_step * grid_step);
    }

    static double derivative_xxs(double x, double y, double f(double x, double y), double grid_step) {
        double u0 = x - EPS;
        double u1 = x;
        double u2 = x + EPS;
        return (f(u0, y) - 2 * f(u1, y) + f(u2, y)) / (grid_step * grid_step);
        //return (u0 - 2 * u1 + u2) / (grid_step * grid_step);
    }

private:
    /* EPS */
    constexpr static const double EPS = 0.00000001f;
};


#endif //MATH_DERIVATIVE_H
