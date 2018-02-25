/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   comdef.hpp
 * Author: mikhail
 *
 * Created on February 25, 2018, 5:59 PM
 */

#ifndef COMDEF_HPP
#define COMDEF_HPP

#include <iostream>

using FT = float;

using Constr = FT(*) (int, const FT*);

/**
 * Box
 */
struct Box {

    /**
     * Constructs an empty box of n dimensions
     */
    Box(int n) {
        mA = new FT[n];
        mB = new FT[n];
        mDim = n;
    }

    ~Box() {
        delete [] mA;
        delete [] mB;
    }

    Box(Box&& box) {
        std::swap(mA, box.mA);
        std::swap(mB, box.mB);
        std::swap(mDim, box.mDim);
    }

    Box& operator=(Box&& box) {
        std::swap(mA, box.mA);
        std::swap(mB, box.mB);
        std::swap(mDim, box.mDim);
        return *this;
    }

    /**
     * Lower bounds
     */
    FT* mA;

    /**
     * Upper bounds
     */
    FT* mB;

    /**
     * Dimension
     */
    int mDim;
};

std::ostream& operator<<(std::ostream& os, const Box& box)  
{  
    const int n = box.mDim;
    for(int i = 0; i < n; i ++) {
        os << "[" << box.mA[i] << ", " << box.mB[i] << "]";
        os << ((i != (n - 1)) ? " x " : "");
    }
    return os;  
}  


/**
 * Defines a problem
 */
struct Problem {
    /**
     * Constructor
     * @param box the bounding box
     * @param constrs the constraints
     */
    Problem(Box& box, std::vector<Constr> constrs) : mBox(box), mConstrs(constrs) {        
    }
    /**
     * Constraints of inequalities (left parts)
     */
    std::vector<Constr> mConstrs;
    /**
     * A bounding box
     */
    const Box& mBox;
};

#endif /* COMDEF_HPP */

