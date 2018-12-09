/*
 * System of inequalities for RPR robot
 */

/* 
 * File:   rpr.hpp
 * Author: mikhail
 *
 * Created on March 11, 2018, 2:04 PM
 */

#ifndef RPR_HPP
#define RPR_HPP

#include <cmath>

#include "comdef.hpp"

constexpr FT getX(FT x, FT r, FT ang) {
    return x + r * cos(ang);
}

constexpr FT getY(FT y, FT r, FT ang) {
    return y + r * sin(ang);
}

constexpr FT getDistQ(FT x, FT y, FT xn, FT yn) {
    return (x - xn) * (x - xn) + (y - yn) * (y - yn);
}

Problem* getRPRProblem() {
    const int n = 3;
    constexpr FT D = 6, d = 2;
    constexpr FT sqrt3 = 1.73205;
    constexpr FT r = d / sqrt3;
    constexpr FT X_1 = 0, Y_1 = 0, X_2 = D, Y_2 = 0, X_3 = 0.5 * D, Y_3 = 0.5 * D * sqrt3;
    constexpr FT A_1 = 7. * M_PI / 6., A_2 = -M_PI/6., A_3 = M_PI / 2.;
    constexpr FT lmin = 1, lmax = D;

    Box *box = new Box(n);
    for (int i = 0; i < 2; i++) {
        box->mA[i] = -d;
        box->mB[i] = D + d;
    }
    box->mA[2] = -M_PI/2;
    box->mB[2] = M_PI/2;
    //box->mA[2] = box->mB[2] = 0;

    std::vector<Constr> vc;
    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_1;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return getDistQ(X_1, Y_1, X, Y) - lmax * lmax;
    });
    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_1;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return -getDistQ(X_1, Y_1, X, Y) + lmin * lmin;
    });

    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_2;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return getDistQ(X_2, Y_2, X, Y) - lmax * lmax;
    });
    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_2;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return -getDistQ(X_2, Y_2, X, Y) + lmin * lmin;
    });


    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_3;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return getDistQ(X_3, Y_3, X, Y) - lmax * lmax;
    });
    vc.emplace_back([] (int n, const FT * x) {
        const FT phi = x[2] + A_3;
        const FT X = getX(x[0], r, phi);
        const FT Y = getY(x[1], r, phi);
        return -getDistQ(X_3, Y_3, X, Y) + lmin * lmin;
    });


    Problem* prob = new Problem(*box, vc,{});
    return prob;
}

#endif /* RPR_HPP */

