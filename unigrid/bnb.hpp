/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bnb.hpp
 * Author: mposypkin
 *
 * Created on March 1, 2018, 12:05 PM
 */

#ifndef BNB_HPP
#define BNB_HPP

#include <vector>
#include "comdef.hpp"
#include "bounder.hpp"

/**
 * A simple branch and bound method
 */
class BnB {
public:

    /**
     * Constructor
     * @param prob the problem to solve
     */
    BnB(const Problem & prob, Bounder& bounder, FT minDiam) : mProblem(prob), mBounder(bounder), mMinDiameter(minDiam) {

    }

    /**
     * Solves the problem
     */
    void solve(std::vector<Box> & inv, std::vector<Box> & outv, std::vector<Box> & boundv) {
        std::vector<Box> pool;
        const int n = mProblem.mBox.mDim;
        Box ibox(n);
        mProblem.mBox.copy(ibox);
        pool.push_back(std::move(ibox));
        while (!pool.empty()) {
            Box box(std::move(pool.back()));
            pool.pop_back();
            Bounder::BoxType bt = mBounder.checkBox(box);
            switch (bt) {
                case Bounder::BoxType::IN:
                    inv.push_back(std::move(box));
                    break;
                case Bounder::BoxType::OUT:
                    outv.push_back(std::move(box));
                    break;
                default:
                    if (box.getDiameterSqr() > mMinDiameter) {
                        Box box1(n), box2(n);
                        box.split(box1, box2);
                        pool.push_back(std::move(box1));
                        pool.push_back(std::move(box2));
                    } else {
                        boundv.push_back(std::move(box));
                    }
                    break;
            }
        }
    }


private:
    const Problem & mProblem;
    const Bounder & mBounder;
    const FT mMinDiameter;
};

#endif /* BNB_HPP */

