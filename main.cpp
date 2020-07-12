#include <iostream>
#include <cmath>
#include <libInterpolate/Interpolators/_2D/BicubicInterpolator.hpp>
#include "Interpolation/Interpolation.h"
#include "Interpolation/Derivative.h"


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

void test2() {
    _2D::BicubicInterpolator<double> interp;

    int nx, ny;
    double xmin, xmax, dx;
    double ymin, ymax, dy;

    nx = 10;
    ny = 5;

    xmin = -1;
    xmax = 8;

    ymin = -1;
    ymax = 3;

    dx = (xmax - xmin)/(nx - 1);
    dy = (ymax - ymin)/(ny - 1);

    _2D::BicubicInterpolator<double>::VectorType xx(nx*ny), yy(nx*ny), zz(nx*ny);

    auto f  = [](double x, double y) { return pow(x,4) + pow(pow(y,2) - 1, 5); };

    for(int i = 0; i < nx*ny; i++)
    {
        // gnuplot format is essentially row-major
        xx(i) = xmin+dx*((double)i/ny);
        yy(i) = ymin+dy*(i%ny);
        zz(i) = f(xx(i),yy(i));
//      std::cerr << xx(i) << " " << yy(i) << ", " << zz(i) << std::endl;
    }


    for(int i = 0; i < nx*ny; i++)
        std::cerr << xx(i) << " " << yy(i) << " " << zz(i) << "\n";

    interp.setData( xx, yy, zz );

    for(int i = 0; i < 4*nx; i++)
    {
        for(int j = 0; j < 5*ny; j++)
        {
            //std::cerr << xmin + dx*i/5. << " " << ymin + dy*j/5. << " " << interp(xmin+dx*i/5., ymin+dy*j/5.) << "\n";
        }
        //std::cerr << "\n";
    }


    //if (ymin + dy*j/5. == 0) {
        //std::cerr << xmin + dx*i/5. << "," << std::endl;
        //std::cerr << Derivative::derivative_xxs(xmin + dx*i/5., ymin + dy*j/5., f, 0.2f) << "," << std::endl;
    //}
}

void test3() {
    _2D::BicubicInterpolator<double> interp;
    int nx = 42;
    int ny = 42;

    _2D::BicubicInterpolator<double>::VectorType xx(nx*ny), yy(nx*ny), zz(nx*ny);

    auto f  = [](double x, double y) { return pow(x,4) + pow(pow(y,2) - 1, 5); };

    double step = 20.0f / 41.0f;
    double current = -10.0f;
    for(int i = 0; i < 42; i++) {
        double inner = -10.0f;
        for (int j = 0; j < 42; j++) {
            xx(i * 42 + j) = current;
            yy(i * 42 + j) = inner;
            zz(i * 42 + j) = f(xx(i), yy(i));
            //std::cerr << i << " " << j << " " << current << " " << inner  << " "  << f(xx(i), yy(i)) << std::endl;
            inner += step;
        }
        current+=step;
    }
//      std::cerr << xx(i) << " " << yy(i) << ", " << zz(i) << std::endl;


    for(int i = 0; i < 42 * 42; i++)
        //std::cerr << i << " " << xx(i) << " " << yy(i) << " " << zz(i) << "\n";

    interp.setData( xx, yy, zz );

    std::vector<double> x_self = {-10.0 ,
                                  -9.75609756097561 ,
                                  -9.512195121951219 ,
                                  -9.268292682926829 ,
                                  -9.024390243902438 ,
                                  -8.78048780487805 ,
                                  -8.536585365853659 ,
                                  -8.292682926829269 ,
                                  -8.048780487804878 ,
                                  -7.804878048780488 ,
                                  -7.560975609756097 ,
                                  -7.317073170731708 ,
                                  -7.073170731707317 ,
                                  -6.829268292682927 ,
                                  -6.585365853658537 ,
                                  -6.341463414634147 ,
                                  -6.097560975609756 ,
                                  -5.853658536585366 ,
                                  -5.609756097560975 ,
                                  -5.365853658536586 ,
                                  -5.121951219512195 ,
                                  -4.878048780487805 ,
                                  -4.634146341463415 ,
                                  -4.390243902439025 ,
                                  -4.146341463414634 ,
                                  -3.902439024390244 ,
                                  -3.6585365853658534 ,
                                  -3.414634146341464 ,
                                  -3.1707317073170733 ,
                                  -2.926829268292683 ,
                                  -2.6829268292682933 ,
                                  -2.439024390243903 ,
                                  -2.1951219512195124 ,
                                  -1.951219512195122 ,
                                  -1.7073170731707314 ,
                                  -1.463414634146341 ,
                                  -1.2195121951219505 ,
                                  -0.9756097560975618 ,
                                  -0.7317073170731714 ,
                                  -0.4878048780487809 ,
                                  -0.24390243902439046 ,
                                  0.0 ,
                                  0.24390243902439046 ,
                                  0.4878048780487809 ,
                                  0.7317073170731696 ,
                                  0.9756097560975601 ,
                                  1.2195121951219505 ,
                                  1.463414634146341 ,
                                  1.7073170731707314 ,
                                  1.951219512195122 ,
                                  2.1951219512195124 ,
                                  2.439024390243903 ,
                                  2.6829268292682933 ,
                                  2.926829268292682 ,
                                  3.1707317073170724 ,
                                  3.414634146341463 ,
                                  3.6585365853658534 ,
                                  3.902439024390244 ,
                                  4.146341463414634 ,
                                  4.390243902439025 ,
                                  4.634146341463413 ,
                                  4.878048780487804 ,
                                  5.121951219512194 ,
                                  5.365853658536585 ,
                                  5.609756097560975 ,
                                  5.853658536585366 ,
                                  6.097560975609756 ,
                                  6.341463414634145 ,
                                  6.585365853658537 ,
                                  6.829268292682926 ,
                                  7.073170731707318 ,
                                  7.317073170731707 ,
                                  7.560975609756099 ,
                                  7.804878048780488 ,
                                  8.048780487804876 ,
                                  8.292682926829269 ,
                                  8.536585365853657 ,
                                  8.78048780487805 ,
                                  9.024390243902438 ,
                                  9.26829268292683 ,
                                  9.512195121951219 ,
                                  9.756097560975608 ,
                                  10.0};

    std::vector<double> y_self = {0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0 ,
                                  0.0
    };

    std::cerr << x_self.size() << std::endl;

    std::vector<double> steps = Derivative::get_steps(x_self);

    std::vector<double> derivatives = Derivative::derivative_xx_const_y(x_self, 0, interp);

    for (auto der : derivatives) {
        std::cerr << der << ", " << std::endl;
    }
    return;

    for (int i = 0; i < x_self.size(); i++) {
        //std::cerr << interp(x_self[i], y_self[i]) << "," << std::endl;
        //std::cerr << f(x_self[i], y_self[i]) << "," << std::endl;
        //std::cerr << Derivative::derivative_xxs(x_self[i], 0, interp, 20.0f / 41.0f) << "," << std::endl;

    }


    /*for (auto x_v : x_self) {
        for (auto y_v : y_self) {
            //std::cerr << x_v << " " << y_v << " " << interp(x_v, y_v) << "," << std::endl;
            std::cerr << x_v << " " << y_v << " " << f(x_v, y_v) << std::endl;
        }
        std::cerr << std::endl;
    }
    return;*/

    step = 20.0f / 41.0f / 5.0f;
    current = -10.0f;
    /*for(int i = 0; i < 41*5; i++)
    {
        double inner = -10.0f;
        for(int j = 0; j < 5*41; j++)
        {
            //std::cerr << i <<  " " << j << " " << current << " " << inner <<  " " << interp(current, inner) << "\n";
            //std::cerr << f(current, inner) << std::endl;
            if (inner == -10.0f) {
                std::cerr << Derivative::derivative_xx(current, inner, interp) << std::endl;
            }
            inner += step;
        }
        current += step;
        //std::cerr << "\n";
    }*/


    //if (ymin + dy*j/5. == 0) {
    //std::cerr << xmin + dx*i/5. << "," << std::endl;
    //std::cerr << Derivative::derivative_xxs(xmin + dx*i/5., ymin + dy*j/5., f, 0.2f) << "," << std::endl;
    //}
}

void derivative_test() {
    //auto func = [](double x, double y) { return pow(x,4) + pow(pow(y,2) - 1, 5); };
    auto func = [](double x, double y) { return x * x * x  + y; };
    double step = 1.0f / 5.0f;

    std::vector<double> x, y, z;
    x.reserve(6 * 5);
    y.reserve(6 * 5);
    z.reserve(6 * 5);

    for (unsigned long i = 0; i < 6; i++) {
        for (unsigned long j = 0; j < 5; j++) {
            double x_v = step * i;
            double y_v = step * j;
            double z_v = func(x_v, y_v);
            x.push_back(x_v);
            y.push_back(y_v);
            z.push_back(z_v);
        }
    }

    _2D::BicubicInterpolator<double> interpolator;
    interpolator.setData(x, y, z);

    for (auto v : x) {
        std::cerr << v << " ";
    }
    std::cerr << std::endl;

    double new_step = 1.0f / 10.0f;
    std::vector<double> steps = Derivative::get_steps(x);
    std::vector<double> derivative = Derivative::derivative_xx_const_y(x, 0, interpolator);

    for (auto der : derivative) {
        //std::cerr << der << std::endl;
    }

}

int main() {
    test3();
    return 0;
}