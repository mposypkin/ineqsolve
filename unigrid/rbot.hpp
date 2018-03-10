/*
 * A simple robot with one link
 */

/* 
 * File:   rbot.hpp
 * Author: mikhail
 *
 * Created on March 9, 2018, 10:35 AM
 */

#ifndef RBOT_HPP
#define RBOT_HPP

#include <cmath>

#include "comdef.hpp"

Problem* getRbotProblem() {
    const int n = 4;
    Box *box = new Box(n);
    for (int i = 0; i < 2; i++) {
        box->mA[i] = -10;
        box->mB[i] = 10;
    }
    box->mA[2] = 0;
    box->mB[2] = M_PI;
    box->mA[3] = 5;
    box->mB[3] = 6;
    
    std::vector<Constr> vc;
    vc.emplace_back([] (int n, const FT* x) {return x[0] - x[3] * cos(x[2]);}) ;
    vc.emplace_back([] (int n, const FT* x) {return x[1] - x[3] * sin(x[2]);}) ;

    Problem* prob = new Problem(*box, {}, vc);
    return prob;
}

#endif /* RBOT_HPP */

