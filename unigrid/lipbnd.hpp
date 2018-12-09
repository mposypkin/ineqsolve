/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lipbnd.hpp
 * Author: mikhail
 *
 * Created on March 8, 2018, 9:49 PM
 */

#ifndef LIPBND_HPP
#define LIPBND_HPP

#include <math.h>
#include <algorithm>
#include "bounder.hpp"
#include "utils.hpp"

/**
 * Lipschitzian bounder
 */
class LipBnd : public Bounder {
public:

    /**
     * The constructor
     * @param np number of points per dimension
     * @param n the dimension
     * @param ibox the initial box
     */
    LipBnd(int np, const Box& ibox) : mNP(np), mIBox(ibox) {
    }

    ~LipBnd() {
    }

    /**
     * Gets the interval containing the values of a constraint when parameters are in a given box.
     * @param box the bounding box
     * @param cons the constraint
     * @return the enclosing interval
     */
    Interval getBound(const Box& box, Constr cons) const {
        const int n = box.mDim;
        const int n1 = n + 1;
        const int sz = getTotalPointsNum(n, mNP) * n1;
        FT* points = new FT[sz];
        
        FT maxCon = -std::numeric_limits<FT>::max();
        FT minCon = std::numeric_limits<FT>::max();
        const int maxn = getTotalPointsNum(n, mNP);
        for (int i = 0; i < maxn; i++) {
            FT * const x = points + i * n1;
            getMeshPoint(i, mNP, box, x);
            const FT v = cons(n, x);
            x[n] = v;
            maxCon = std::max(v, maxCon);
            minCon = std::min(v, minCon);
        }
        FT q = 0;
        for (int i = 0; i < n; i++) {
            FT delt = ((box.mB[i] - box.mA[i]) / (mNP - 1));
            q += delt * delt;
        }
        const FT L = getLip(n, points);
        const FT d = sqrt(q);
        const FT gamma = 1 + box.getDiameterSqr()/mIBox.getDiameterSqr();

        //std::cout << "ld = " << L * d << "\n";
        maxCon += gamma * L * d;
        minCon -= gamma * L * d;
        delete [] points;
        return std::make_pair(minCon, maxCon);
    }

private:

    FT getLip(int n, FT* points) const {
        const int n1 = n + 1;
        FT l = 0;
//#pragma omp parallel for        
        for (int i = 0; i < mNP; i++) {
            for (int j = i + 1; j < mNP; j++) {
                FT dr = dist(n, points + i * n1, points + j * n1);
                FT dv = fabs(points[i * n1 + n] - points[j * n1 + n]);
                FT ln = dv / dr;
                l = std::max(l, ln);
            }
        }
        return l;
    }

    FT dist(int n, const FT * const x, const FT * const y) const {
        FT q = 0;
        for (int i = 0; i < n; i++) {
            FT r = x[i] - y[i];
            q += r * r;
        }
        return sqrt(q);
    }

    const int mNP;
    const Box& mIBox;
    
};


#endif /* LIPBND_HPP */

