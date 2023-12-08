#include "FiniteFunctions.h"
#include <vector>
#include <algorithm>
#include <iostream>



int main(){

    std::vector<double> importVals;
    importVals = ReadFunc("Outputs/data/MysteryData13120.txt");

    std::vector<double>::iterator m_RMin = std::min_element(importVals.begin(), importVals.end());
    std::vector<double>::iterator m_RMax = std::max_element(importVals.begin(), importVals.end());

    FiniteFunction func(*m_RMin,*m_RMax,"Output");
    func.plotFunction();
    func.plotData(importVals,100);

    GaussFunction gfunc(*m_RMin,*m_RMax,0,1,"Output_Gauss");
    gfunc.plotFunction();
    gfunc.plotData(importVals,100);

    CauchyLorentzFunction cfunc(*m_RMin,*m_RMax,0,2,"Output_CL");
    cfunc.plotFunction();
    cfunc.plotData(importVals,100);

    CrystalBallFunction crfunc(*m_RMin,*m_RMax,2, 0.5, 1.2,"Output_Crystal");
    crfunc.plotFunction();
    crfunc.plotData(importVals,100);


    return 0;
}