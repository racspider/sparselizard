#ifndef HARMONIC_H
#define HARMONIC_H

#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include "universe.h"
#include "densematrix.h"

namespace harmonic
{
    // Get the coefficient by which to multiply the fundamental frequency:
    int getfrequency(int harmonicnumber);
    
    bool issine(int harmonicnumber);
    bool iscosine(int harmonicnumber);
    
    int getharmonicnumber(int frequency, bool issine);
    int getharmonicnumber(std::string input);
    
    // Get all harmonic numbers (and multiplying coefficients) in the sum 
    // of harmonics resulting from the product of the two input harmonics.
    std::vector<std::pair<int,double>> getproduct(int harm1, int harm2);
    // Get the same but when an order 'harm2timederivativeorder' 
    // time derivative is applied to harmonic 'harm2'. 
    std::vector<std::pair<int,double>> getproduct(int harm1, int harm2, int harm2timederivativeorder);
    
    // Get the derivation factors (i.e. the wi and -wi^2) for the harmonic.
    double getderivationfactor(int timederivativeorder, int harm);
    // Apply the time derivative to 'input':
    std::vector<std::vector<densematrix>> timederivative(int timederivativeorder, std::vector<std::vector<densematrix>> input);
};

#endif
