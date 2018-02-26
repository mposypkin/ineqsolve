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

    BoxType checkBox(const Box& box) {
        std::cout << "Checking box " << box << "\n";
        const int n = box.mDim;
        std::vector<FT> delt(n);
        std::vector<int> cnt(n, 0);
        std::vector<FT> x(n);
        int maxn = 1;
        for (int i = 0; i < n; i++) {
            delt[i] = ((box.mB[i] - box.mA[i]) / (mNP - 1));
            maxn *= mNP;
        }
        for (int i = 0; i < maxn; i++) {
            getVec(i, n, cnt);
            for (auto j : cnt) {
                std::cout << j << "\t";
            }
            std::cout << std::endl;
            for (int j = 0; j < n; j++) {
                x[j] = box.mA[j] + delt[j] * cnt[j];
            }
            for (auto y : x) {
                std::cout << y << "\t";
            }
            std::cout << std::endl;
            int k = 0;
            for(auto cons : mProblem.mConstrs) {
                auto v = cons(n, x.data());
                std::cout << "v[" << k ++ << "] = " << v << "\n";
            }
            std::cout << std::endl;
        }
    }

private:

    void getVec(int i, int n, std::vector<int>& cnt) {
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

