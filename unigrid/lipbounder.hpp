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

#ifndef LIPBOUNDER_HPP
#define LIPBOUNDER_HPP

#include <math.h>
#include <limits>
#include "comdef.hpp"
#include "bounder.hpp"

/**
 * Lipschitzian bounder
 */
class LipBounder : public Bounder {
public:

    /**
     * Constructor
     * @param prob the problem to solve
     * @param np the number of points per dimension
     */
    LipBounder(const Problem & prob, int np) : mProblem(prob), mNP(np) {
        const int n = prob.mBox.mDim;
        int maxn = 1;
        for (int i = 0; i < n; i++) {
            maxn *= mNP;
        }
        mNumPoints = maxn;
        const int sz = mNumPoints * (n + 1);
        mPoints = new FT[sz];
    }
    
    ~LipBounder() {
        delete [] mPoints;
    }

    BoxType checkBox(const Box & box) const {
        const int n = box.mDim;
        std::vector<FT> delt(n);
        std::vector<int> cnt(n, 0);
        FT maxCon = -std::numeric_limits<FT>::max();
        FT minCon = std::numeric_limits<FT>::max();
        for (int i = 0; i < n; i++) {
            delt[i] = ((box.mB[i] - box.mA[i]) / (mNP - 1));
        }
        for (int i = 0; i < mNumPoints; i++) {
            getVec(i, n, cnt);
            for (int j = 0; j < n; j++) {
                mPoints[i * (n + 1) + j] = box.mA[j] + delt[j] * cnt[j];
            }
            FT v = getPhi(mPoints + i * (n + 1));
            mPoints[i * (n + 1) + n] = v;
            maxCon = std::max(v, maxCon);
            minCon = std::min(v, minCon);
        }


        FT q = 0;
        for (int i = 0; i < n; i++) {
            q += delt[i] * delt[i];
        }
        const FT L = getLip();
        const FT d = sqrt(q);
        maxCon += L * d;
        minCon -= L * d;

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

    FT getLip() const {
        const int n = mProblem.mBox.mDim;
        const int n1 = n + 1;
        FT l  = 0;
        for(int i = 0; i < mNumPoints; i ++) {
            for(int j = i + 1; j < mNumPoints; j ++) {
                FT dr = dist(mPoints + i * n1, mPoints + j * n1);
                FT dv = fabs(mPoints[i * n1 + n] - mPoints[j * n1 + n]);
                FT ln = dv / dr;
                l = std::max(l, ln);
            }
        }
        return l;
    }

    FT dist(FT* x, FT* y) const {
        const int n = mProblem.mBox.mDim;
        FT q = 0;
        for(int i = 0; i < n; i ++) {
            FT r = x[i] - y[i];
            q += r * r;
        }
        return sqrt(q);
    }
    
    FT getPhi(FT * x) const {
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
    FT* mPoints;
    int mNumPoints;

};


#endif /* LIPBOUNDER_HPP */

