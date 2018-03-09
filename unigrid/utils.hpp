/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.hpp
 * Author: mikhail
 *
 * Created on March 8, 2018, 7:52 PM
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "comdef.hpp"

/**
 * Get the total number of points in the mesh
 * @param n the dimension of a vector
 * @param np number of points per dimension
 * @return the total number of points
 */
int getTotalPointsNum(int n, int np) {
    int rv = 1;
    for(int i = 0; i < n; i ++) {
        rv *= np;
    }
    return rv;
}

/**
 * Get mesh point
 * @param ci the number of current point
 * @param np the number of points per dimension
 * @param box the box
 * @param x the resulting mesh point
 */
void getMeshPoint(int ci, int np,  const Box& box, FT* x) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
        const int d = ci % np;
        const int ind = d;
        ci -= d;
        ci /= np;
        FT delt = ((box.mB[i] - box.mA[i]) / (np - 1));
        x[i] = box.mA[i] + delt * ind;
    }
}

#endif /* UTILS_HPP */

