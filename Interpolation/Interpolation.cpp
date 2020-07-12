#include "Interpolation.h"

#include <iostream>

#include <libInterpolate/Interpolate.hpp>
#include "Derivative.h"

// Created by Иван Морозов on 2020-07-06.

void Interpolation::cubicInterpolation(std::vector<double> x,
        std::vector<double> y, std::vector<double> z, double f(double x, double y)) {
    const int size_x = x.size();
    const int size_y = y.size();
    const int size_z = z.size();

    _2D::BicubicInterpolator<double> interpolator;
    interpolator.setData(x, y, z);

    double step = 20.0f / 41.0f / 5.0f;
    double current = -10.0f; // x
    /*for (int i = 0; i < 41 * 5; i++) {
        double inner_current = -10.0f; // y
        for (int j = 0; j < 41 * 5; j++) {
            if (inner_current == -10.0f) {
               std::cerr << Derivative::derivative_with_steps(current, inner_current, interpolator, step) << "," << std::endl;
            }
            inner_current += step;
        }
        current += step;
    }*/
}
