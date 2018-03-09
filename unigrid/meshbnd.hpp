/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   meshbnd.hpp
 * Author: mikhail
 *
 * Created on March 8, 2018, 7:48 PM
 */

#ifndef MESHBND_HPP
#define MESHBND_HPP

#include <algorithm>
#include "bounder.hpp"
#include "utils.hpp"
/**
 * A mesh bounder
 */
class MeshBnd : public Bounder {
public:
    
    /**
     * The constructor
     * @param np number of points
     */
    MeshBnd(int np) : mNP(np) {
        
    }

    /**
     * Gets the interval containing the values of a constraint when parameters are in a given box.
     * @param box the bounding box
     * @param cons the constraint
     * @return the enclosing interval
     */
    Interval getBound(const Box& box, Constr cons) const {
        const int n = box.mDim;
        std::vector<FT> x(n);
        FT maxCon = -std::numeric_limits<FT>::max();
        FT minCon = std::numeric_limits<FT>::max();
        const int maxn = getTotalPointsNum(n, mNP);
        for (int i = 0; i < maxn; i++) {
            getMeshPoint(i, mNP, box, x.data());
            FT v = cons(n, x.data());
            maxCon = std::max(v, maxCon);
            minCon = std::min(v, minCon);
        }
        return std::make_pair(minCon, maxCon);
    }
    
private:

    const int mNP;
};


#endif /* MESHBND_HPP */

