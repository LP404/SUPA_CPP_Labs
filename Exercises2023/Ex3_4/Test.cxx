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


    std::vector<double> GaussMet;
    std::vector<double> CauchLorMet;
    std::vector<double> CrystalMet;
    int samSize = 1000;

    GaussMet = gfunc.VectorMaker(samSize);
    CauchLorMet = cfunc.VectorMaker(samSize);
    CrystalMet = crfunc.VectorMaker(samSize);


///I've checked this part of the code and the values it outputs appear to be in line with the other data, but it plots weird
//It does not generate a value over 0.4X, but it appears to plot a value that is at least 3

    for (int i=0; i<samSize; i++) {
        GaussMet[i] = gfunc.callFunction(GaussMet[i]);
        CauchLorMet[i] = cfunc.callFunction(CauchLorMet[i]);
        CrystalMet[i] = crfunc.callFunction(CrystalMet[i]);
    }


   for (int i=0; i<samSize; i++) {
        GaussMet[i+1] = gfunc.Metropolis(GaussMet[i],0,0.5);
        CauchLorMet[i+1] = cfunc.Metropolis(CauchLorMet[i],0,0.5);
        CrystalMet[i+1] = crfunc.Metropolis(CrystalMet[i],0,0.5);
    }

    gfunc.plotData(GaussMet,100,false);
    cfunc.plotData(CauchLorMet,100,false);
    crfunc.plotData(CrystalMet,100,false);


    return 0;
}