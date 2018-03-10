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
#include <functional>
#include <utility>

using FT = float;

//using Constr = FT(*) (int, const FT*);
using Constr = std::function<FT(int, const FT*)>;

using Interval = std::pair<FT, FT>;

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
        mA = box.mA;
        mB = box.mB;
        mDim = box.mDim;
        box.mA = nullptr;
        box.mB = nullptr;
    }

    Box& operator=(Box&& box) {
        std::swap(mA, box.mA);
        std::swap(mB, box.mB);
        std::swap(mDim, box.mDim);
        return *this;
    }

    /**
     * Copies the box
     * @param nbox new box to fill in
     */
    void copy(Box& nbox) const {
        for (int i = 0; i < mDim; i++) {
            nbox.mA[i] = mA[i];
            nbox.mB[i] = mB[i];
        }
    }

    /**
     * Splits the box across the longest edge
     * @param box1 first resulting box
     * @param box2 second resulting box
     */
    void split(Box& box1, Box& box2) const {
        int maxd = 0;
        FT maxl = mB[0] - mA[0];
        for (int i = 0; i < mDim; i++) {
            const FT newl = mB[i] - mA[i];
            if (newl > maxl) {
                maxl = newl;
                maxd = i;
            }
        }
        copy(box1);
        copy(box2);
        box1.mB[maxd] = box1.mA[maxd] + 0.5 * maxl;
        box2.mA[maxd] = box2.mB[maxd] - 0.5 * maxl;
    }

    /**
     * Returns the squared diameter of the box
     * @return diameter squared
     */
    FT getDiameterSqr() const {
        FT d = 0;
        for (int i = 0; i < mDim; i++) {
            const FT v = mB[i] - mA[i];
            d += v * v;
        }
        return d;
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

std::ostream& operator<<(std::ostream& os, const Box& box) {
    const int n = box.mDim;
    for (int i = 0; i < n; i++) {
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
    Problem(Box& box, std::vector<Constr> iconstrs, std::vector<Constr> econstrs) : mBox(box), mIneqConstrs(iconstrs), mEqConstrs(econstrs) {
    }
    /**
     * Constraints of inequalities (left parts)
     */
    std::vector<Constr> mIneqConstrs;

    /**
     * Equality constraints (left parts)
     */
    std::vector<Constr> mEqConstrs;
    /**
     * A bounding box
     */
    const Box& mBox;
};

#endif /* COMDEF_HPP */

