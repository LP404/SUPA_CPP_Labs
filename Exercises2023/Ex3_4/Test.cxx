#include "FiniteFunctions2.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>



int main(){

    std::vector<double> importVals;
    importVals = ReadFunc("Outputs/data/MysteryData13120.txt");

    std::vector<double>::iterator m_RMin = std::min_element(importVals.begin(), importVals.end());
    std::vector<double>::iterator m_RMax = std::max_element(importVals.begin(), importVals.end());

    double Average;

    

    FiniteFunction func(*m_RMin,*m_RMax,"Output");
    func.plotFunction();
    func.plotData(importVals,100);
    func.printInfo();

    Ex34Functions gfunc(*m_RMin,*m_RMax,"Output_Gauss");
    gfunc.selectDist = 0;
    gfunc.SetGaussParams(0,3);
    gfunc.plotFunction();
    gfunc.plotData(importVals,100);

    Ex34Functions cfunc(*m_RMin,*m_RMax,"Output_CL");
    cfunc.selectDist = 1;
    cfunc.SetCauchLorParams(0,2);
    cfunc.plotFunction();
    cfunc.plotData(importVals,100);

    Ex34Functions crfunc(*m_RMin,*m_RMax,"Output_Crystal");
    crfunc.selectDist = 2;
    Average = std::reduce(importVals.begin(), importVals.end(), 0.0) / importVals.size();
    crfunc.SetCrystalParams(1,1,1);
    crfunc.plotFunction();
    crfunc.plotData(importVals,100);


    return 0;
}