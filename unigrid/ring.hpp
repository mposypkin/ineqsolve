/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ring.hpp
 * Author: mikhail
 *
 * Created on February 25, 2018, 2:23 PM
 */

#ifndef RING_HPP
#define RING_HPP

#include "comdef.hpp"


constexpr FT r1 = 6;

constexpr FT r2 = 5.7;

FT constr1(int n, const FT* x) {
    FT v = 0;
    for (int i = 0; i < n; i++) {
        v += x[i] * x[i];
    }
    return v - r1 * r1;
}

FT constr2(int n, const FT* x) {
    FT v = 0;
    for (int i = 0; i < n; i++) {
        v += x[i] * x[i];
    }
    return r2 * r2 - v;
}

Problem* getRingProblem(int n) {
    Box *box = new Box(n);
    for (int i = 0; i < n; i++) {
        box->mA[i] = -10;
        box->mB[i] = 10;
    }
    
    std::vector<Constr> vc;
    vc.push_back(constr1);
    vc.push_back(constr2);

    Problem* prob = new Problem(*box, vc);
    return prob;
}
#endif /* RING_HPP */

