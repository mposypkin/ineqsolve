/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ringseq.hpp
 * Author: mikhail
 *
 * Created on March 9, 2018, 10:19 AM
 */

#ifndef RINGSEQ_HPP
#define RINGSEQ_HPP

#include "comdef.hpp"

/**
 * The constraint for one ring
 */
struct RingConstr {

    /**
     * Constructor 
     * @param c the coordinates of a center
     * @param rad the radius
     */
    RingConstr(const std::vector<FT>& c, FT rad) :
    mC(c), mRadQ(rad * rad) {
    }

    FT operator()(int n, const FT* x) {
        FT v = 0;
        for (int i = 0; i < n; i++) {
            v += (mC[i] - x[i]) * (mC[i] - x[i]);
        }
        FT rv = mRadQ - v ;
        return rv;
    }

    std::vector<FT> mC;
    FT mRadQ;
};

Problem* getRingsEqProblem(int n) {
    Box *box = new Box(n);
    for (int i = 0; i < n; i++) {
        box->mA[i] = -10;
        box->mB[i] = 10;
    }

    std::vector<Constr> vc;
    vc.emplace_back(RingConstr({0, 0}, 3));
    vc.emplace_back(RingConstr({2, 0}, 3));

    Problem* prob = new Problem(*box, {}, vc);
    return prob;
}




#endif /* RINGSEQ_HPP */

