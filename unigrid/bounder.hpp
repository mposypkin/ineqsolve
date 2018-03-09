/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bounder.hpp
 * Author: mikhail
 *
 * Created on March 8, 2018, 7:34 PM
 */

#ifndef BOUNDER_HPP
#define BOUNDER_HPP

#include "comdef.hpp"

/**
 * Abstract class for computing bounds 
 */
class Bounder {
public:
    
    
    virtual Interval getBound(const Box& box, Constr cons) const = 0;     
       
};

#endif /* BOUNDER_HPP */

