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
#include <algorithm>
#include <omp.h>
#include "comdef.hpp"
#include "boxsort.hpp"

/**
 * A simple branch and bound method
 */
class BnB {
public:

    /**
     * Constructor
     * @param prob the problem to solve
     */
    BnB(const Problem & prob, BoxSort& bounder, FT minDiam) : mProblem(prob), mBounder(bounder), mMinDiameter(minDiam) {

    }

    /**
     * Solves the problem
     * @param inv inner boxes
     * @param outv outer boxes
     * @param boundv boundary boxes
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
            BoxSort::BoxType bt = mBounder.checkBox(box);
            switch (bt) {
                case BoxSort::BoxType::IN:
                    inv.push_back(std::move(box));
                    break;
                case BoxSort::BoxType::OUT:
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

    /**
     * Solves the problem in parallel with critical sections
     * @param inv inner boxes
     * @param outv outer boxes
     * @param boundv boundary boxes
     */
    void solveOMPSimple(std::vector<Box> & inv, std::vector<Box> & outv, std::vector<Box> & boundv) {
        const int n = mProblem.mBox.mDim;
        constexpr int masterThread = 0;
        std::vector<std::vector < Box > > poolVector;
        std::vector<std::vector < Box > > poolVectorNew;

        int totalSize = 0;
#pragma omp parallel num_threads(16)
        {
            std::vector<Box> linv, loutv, lboundv;
            const int nt = omp_get_thread_num();
            const int totalThreads = omp_get_num_threads();
#pragma omp single
            {
                poolVector.resize(totalThreads);
                poolVectorNew.resize(totalThreads);
                Box ibox(n);
                mProblem.mBox.copy(ibox);
                poolVectorNew[masterThread].push_back(std::move(ibox));
            }
            while (true) {
#pragma omp single
                {
                    totalSize = 0;
                    for (auto &pool : poolVectorNew)
                        totalSize += pool.size();
                    if (totalSize > 0) {
                        std::swap(poolVector, poolVectorNew);
                        for (auto &pool : poolVectorNew)
                            pool.clear();
                    }
                }
                //                std::cout << "totalSize = " << totalSize << "\n";
                if (totalSize == 0) {
#pragma omp critical
                    {
                        appendBoxVector(linv, inv);
                        appendBoxVector(loutv, outv);
                        appendBoxVector(lboundv, boundv);
                        //inv.insert(inv.end(), linv.begin(), linv.end());
//                        outv.insert(outv.end(), loutv.begin(), loutv.end());
//                        boundv.insert(boundv.end(), boundv.begin(), boundv.end());
                    }
                    break;
                }
                    
                for (auto &pool : poolVector) {
                    const int poolSize = pool.size();
#pragma omp for                
                    for (int i = 0; i < poolSize; i++) {
                        Box box(std::move(pool[i]));
                        BoxSort::BoxType bt;
                        bt = mBounder.checkBox(box);
                        switch (bt) {
                            case BoxSort::BoxType::IN:
                                linv.push_back(std::move(box));
                                break;
                            case BoxSort::BoxType::OUT:
                                loutv.push_back(std::move(box));
                                break;
                            default:
                                if (box.getDiameterSqr() > mMinDiameter) {
                                    Box box1(n), box2(n);
                                    box.split(box1, box2);
                                    poolVectorNew[nt].push_back(std::move(box1));
                                    poolVectorNew[nt].push_back(std::move(box2));
                                } else {
                                    lboundv.push_back(std::move(box));
                                }
                                break;
                        }
                    }
                }
            }
        }
    }


private:
    
    void appendBoxVector(std::vector<Box>& src, std::vector<Box>& dst){
        std::move(std::begin(src), std::end(src), std::back_inserter(dst));
    }
    const Problem & mProblem;
    const BoxSort & mBounder;
    const FT mMinDiameter;
};

#endif /* BNB_HPP */

