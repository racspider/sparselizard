#include "opconstant.h"


std::vector<std::vector<densematrix>> opconstant::interpolate(elementselector& elemselect, std::vector<double>& evaluationcoordinates, expression* meshdeform)
{
	densematrix output(elemselect.countinselection(), evaluationcoordinates.size()/3, constantvalue);
    
    // The constant is on the cos0 harmonic:
	return {{},{output}};
}

densematrix opconstant::multiharmonicinterpolate(int numtimeevals, elementselector& elemselect, std::vector<double>& evaluationcoordinates, expression* meshdeform)
{
    densematrix output(numtimeevals, elemselect.countinselection() * evaluationcoordinates.size()/3, constantvalue);
    
    return output;
}

std::shared_ptr<operation> opconstant::copy(void)
{
    std::shared_ptr<opconstant> op(new opconstant(constantvalue));
    *op = *this;
    op->reuse = false;
    return op;
}

void opconstant::print(void) { std::cout << constantvalue; }
