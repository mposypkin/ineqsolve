/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rbotineq.hpp
 * Author: mikhail
 *
 * Created on March 10, 2018, 11:34 AM
 */

#ifndef RBOTINEQ_HPP
#define RBOTINEQ_HPP

#include <cmath>

#include "comdef.hpp"

FT theta(FT x, FT y) {
    FT rv;
    if(x == 0 && y == 0)
        return rv;
    else{
        FT v = acos(x / sqrt(x * x + y * y));
        if(y >= 0)
            rv = v;
        else
            rv = 2 * M_PI - v;        
    } 
    return rv;
}

Problem* getRbotIneqProblem() {
    const int n = 2;
    Box *box = new Box(n);
    for (int i = 0; i < 2; i++) {
        box->mA[i] = -10;
        box->mB[i] = 10;
    }
    constexpr FT lmin = 5;
    constexpr FT lmax = 6;
    constexpr FT thmin = 0;
    constexpr FT thmax = M_PI;
    std::vector<Constr> vc;
    vc.emplace_back([] (int n, const FT * x) {
        return x[0] * x[0] + x[1] * x[1] - lmax * lmax;
    });
    vc.emplace_back([] (int n, const FT * x) {
        return -x[0] * x[0] - x[1] * x[1] + lmin * lmin;
    });
    vc.emplace_back([] (int n, const FT * x) {
        return theta(x[0], x[1]) - thmax;
    });
    vc.emplace_back([] (int n, const FT * x) {
        return -theta(x[0], x[1]) + thmin;
    });
    Problem* prob = new Problem(*box, vc,{});
    return prob;
}

#endif /* RBOTINEQ_HPP */

