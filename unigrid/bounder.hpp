/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bounder.hpp
 * Author: mposypkin
 *
 * Created on February 26, 2018, 4:35 PM
 */

#ifndef BOUNDER_HPP
#define BOUNDER_HPP

#include "comdef.hpp"

/**
 * Qualifies  boxes
 */
class Bounder {
public:

    /**
     * Possible types for box qualification
     */
    enum BoxType {
        // the box is inside
        IN,
        // the box is outside
        OUT,
        // the box is boundary
        BOUND
    };
    
    /**
     * Evaluates and returns the type of the box
     * @param box parameter
     * @return the box's type
     */
    virtual BoxType checkBox(const Box& box) const = 0;
};


#endif /* BOUNDER_HPP */

