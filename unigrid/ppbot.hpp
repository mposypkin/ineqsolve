/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ppbot.hpp
 * Author: mikhail
 *
 * Created on March 3, 2018, 11:21 AM
 */

#ifndef PPBOT_HPP
#define PPBOT_HPP

#include "comdef.hpp"

/**
 * The constraint for a link
 */
struct PPLinkConstr {

    /**
     * Constructor 
     * @param c the coordinates of a fixed joint
     * @param lcons minimal (or maximal) link length
     * @param ismin true if the constraint is for a minimal link length
     */
    PPLinkConstr(const std::vector<FT>& c, FT lcons, bool ismin) :
    mC(c), mLconsQ(lcons * lcons), mIsMin(ismin) {
    }

    FT operator()(int n, const FT* x) {
        FT v = 0;
        for (int i = 0; i < n; i++) {
            v += (mC[i] - x[i]) * (mC[i] - x[i]);
        }
        FT rv = mIsMin ? mLconsQ - v : v - mLconsQ;
        return rv;
    }

    std::vector<FT> mC;
    FT mLconsQ;
    bool mIsMin;
};

Problem* getPPbotProblem(int n) {
    Box *box = new Box(n);
    for (int i = 0; i < n; i++) {
        box->mA[i] = -10;
        box->mB[i] = 10;
    }

    std::vector<Constr> vc;
    vc.emplace_back(PPLinkConstr({0, 0}, 3, true));
    vc.emplace_back(PPLinkConstr({0, 0}, 8, false));
    vc.emplace_back(PPLinkConstr({5, 0}, 3, true));
    vc.emplace_back(PPLinkConstr({5, 0}, 8, false));

    Problem* prob = new Problem(*box, vc, {});
    return prob;
}



#endif /* PPBOT_HPP */

