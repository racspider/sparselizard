#ifndef LAGRANGEQUADRANGLE_H
#define LAGRANGEQUADRANGLE_H

#include <vector>
#include "polynomial.h"
#include "math.h"
#include "element.h"


namespace lagrangequadrangle
{
    // 'getnodecoordinates' gives the ki, eta and phi 
    // coordinates of every Lagrange node for the required order:
    std::vector<double> getnodecoordinates(int order);
    // 'getformfunctionpolynomials' outputs a vector giving the form function polynomials:
    std::vector<polynomial> getformfunctionpolynomials(int order);
}

#endif