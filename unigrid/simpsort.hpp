/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simpsort.hpp
 * Author: mikhail
 *
 * Created on March 8, 2018, 8:47 PM
 */

#ifndef SIMPSORT_HPP
#define SIMPSORT_HPP

#include <iostream>
#include "comdef.hpp"
#include "boxsort.hpp"
#include "bounder.hpp"

/**
 * A simple sorter
 */
class SimpSort : public BoxSort {
public:

    /**
     * Constructor
     * @param prob the problem to solve
     * @param bnd the bounder to use
     */
    SimpSort(const Problem& prob, const Bounder& bnd, FT delt = 0) : mBnd(bnd), mProb(prob) {
    }

    BoxType checkBox(const Box& box) const {
        BoxSort::BoxType bt = BoxSort::BoxType::IN;

        for (auto ineqc : mProb.mIneqConstrs) {
            auto interv = mBnd.getBound(box, ineqc);
//            std::cout << "[" << interv.first << " : " << interv.second << "]\n";
            if (interv.first > 0) {
                bt = BoxSort::BoxType::OUT;
                break;
                
            } else if (interv.second > 0) {
                bt = BoxSort::BoxType::BOUND;
            }
        }
//        std::cout << "-------------\n";
        return bt;
    }

private:
    const Bounder& mBnd;
    const Problem& mProb;    
};

#endif /* SIMPSORT_HPP */

