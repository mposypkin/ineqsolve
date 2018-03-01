/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   meshBounder.hpp
 * Author: mposypkin
 *
 * Created on February 26, 2018, 4:44 PM
 */

#ifndef MESHBOUNDER_HPP
#define MESHBOUNDER_HPP

#include <limits>
#include "comdef.hpp"
#include "bounder.hpp"

/**
 * A simple mesh bounder
 */
class MeshBounder : public Bounder {
public:

    /**
     * Constructor
     * @param prob the problem to solve
     * @param np the number of points per dimension
     */
    MeshBounder(const Problem & prob, int np) : mProblem(prob), mNP(np) {

    }

    BoxType checkBox(const Box& box) const {
        const int n = box.mDim;
        std::vector<FT> delt(n);
        std::vector<int> cnt(n, 0);
        std::vector<FT> x(n);
        FT maxCon = -std::numeric_limits<FT>::max();
        FT minCon = std::numeric_limits<FT>::max();
        int maxn = 1;
        for (int i = 0; i < n; i++) {
            delt[i] = ((box.mB[i] - box.mA[i]) / (mNP - 1));
            maxn *= mNP;
        }
        for (int i = 0; i < maxn; i++) {
            getVec(i, n, cnt);
            for (int j = 0; j < n; j++) {
                x[j] = box.mA[j] + delt[j] * cnt[j];
            }
            FT v = getPhi(x.data());
            maxCon = std::max(v, maxCon);
            minCon = std::min(v, minCon);
        }

        Bounder::BoxType bt;
        if (maxCon <= 0)
            bt = Bounder::BoxType::IN;
        else if (minCon > 0)
            bt = Bounder::BoxType::OUT;
        else
            bt = BoxType::BOUND;

        return bt;
    }

private:

    FT getPhi(FT* x) const {
        const int n = mProblem.mBox.mDim;
        FT v = -std::numeric_limits<FT>::max();
        for (auto cons : mProblem.mConstrs) {
            v = std::max(v, cons(n, x));
        }
        return v;
    }

    void getVec(int i, int n, std::vector<int>& cnt) const {
        for (int j = 0; j < n; j++) {
            int d = i % mNP;
            cnt[j] = d;
            i -= d;
            i /= mNP;
        }
    }

    const Problem & mProblem;
    const int mNP;
};


#endif /* MESHBOUNDER_HPP */

