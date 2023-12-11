#include "FiniteFunctions2.h"
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

///Put numeric everywhere to try and get rid of an error


int main(){

    std::vector<double> importVals;
    Ex34Functions rfunc;
    importVals = rfunc.ReadFunc("Outputs/data/MysteryData13120.txt");

    std::vector<double>::iterator m_RMin = std::min_element(importVals.begin(), importVals.end());
    std::vector<double>::iterator m_RMax = std::max_element(importVals.begin(), importVals.end());

    double Average;

    

    FiniteFunction func(*m_RMin,*m_RMax,"Output");
    func.plotFunction();
    func.plotData(importVals,100);
    func.printInfo();

    Ex34Functions gfunc(*m_RMin,*m_RMax,"Output_Gauss");
    gfunc.selectDist = 0;
    gfunc.SetGaussParams(0,1);
    gfunc.plotFunction();
    gfunc.plotData(importVals,100);
    gfunc.printInfo();

    Ex34Functions cfunc(*m_RMin,*m_RMax,"Output_CL");
    cfunc.selectDist = 1;
    cfunc.SetCauchLorParams(0,0.75);
    cfunc.plotFunction();
    cfunc.plotData(importVals,100);
    cfunc.printInfo();

    Ex34Functions crfunc(*m_RMin,*m_RMax,"Output_Crystal");
    crfunc.selectDist = 2;
    Average = std::reduce(importVals.begin(), importVals.end(), 0.0) / importVals.size();
    crfunc.SetCrystalParams(1,1,1);
    crfunc.plotFunction();
    crfunc.plotData(importVals,100);
    crfunc.printInfo();


    return 0;
}