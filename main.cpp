#include <iostream>
#include <cmath>

#include "Interpolation/Interpolation.h"


/*
 * 41 points at range[-10;10]
 * */
void test1() {
    double step = 20.0f / 41.0f;  // step range / points_count

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;

    auto function = [](double x, double y) {return pow(x, 4) + pow(pow(y, 2) - 1, 5);};
    double current = -10.0f; // x
    /* заполняем сетку */
    for (int i = 0; i < 41; i++) {
        double inner_current = -10.0f; // y
        for (int j = 0; j < 41; j++) { /* [x,y,z] */
            x.push_back(current);
            y.push_back(inner_current);
            z.push_back(function(current, inner_current));
            inner_current += step;
        }
        current += step;
    }

    Interpolation interpolation;
    interpolation.cubicInterpolation(x, y, z, function);
}

int main() {
    test1();
    return 0;
}