#include "FiniteFunctions2.h"
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

///Put numeric everywhere to try and get rid of an error
///The negative Crystal ball function only plots right roughly half of the time and I don't know why. If I had more time I'd look into it properly
///Just run it again if it doesn't plot right

int main(){

    std::vector<double> importVals;
    Ex34Functions rfunc;
    importVals = rfunc.ReadFunc("Outputs/data/MysteryData13120.txt");

    std::vector<double>::iterator m_RMin = std::min_element(importVals.begin(), importVals.end());
    std::vector<double>::iterator m_RMax = std::max_element(importVals.begin(), importVals.end());

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

    //I was having problems with calcualting the average so that is done outside the functions file and fed into it
    double Average;

    Ex34Functions crfunc(*m_RMin,*m_RMax,"Output_Crystal");
    crfunc.selectDist = 2;
    Average = std::reduce(importVals.begin(), importVals.end(), 0.0) / importVals.size();
    crfunc.SetCrystalAverage(Average);
    crfunc.SetCrystalParams(1,1,1);
    crfunc.plotFunction();
    crfunc.plotData(importVals,100);
    crfunc.printInfo();


    std::vector<double> GaussMet;
    std::vector<double> CauchLorMet;
    std::vector<double> CrystalMet;
    
    int samSize = 100000;

    GaussMet = gfunc.VectorMaker(samSize);
    CauchLorMet = cfunc.VectorMaker(samSize);
    CrystalMet = crfunc.VectorMaker(samSize);

    for (int i=0; i<samSize; i++) {
        GaussMet[i] = gfunc.callFunction(GaussMet[i]);
        CauchLorMet[i] = cfunc.callFunction(CauchLorMet[i]);
        CrystalMet[i] = crfunc.callFunction(CrystalMet[i]);
    }

   for (int i=0; i<samSize; i++) {
        GaussMet[i+1] = gfunc.Metropolis(GaussMet[i],0,0.25);
        CauchLorMet[i+1] = cfunc.Metropolis(CauchLorMet[i],0,0.25);
        CrystalMet[i+1] = crfunc.Metropolis(CrystalMet[i],0,3);
    }

    gfunc.plotData(GaussMet,100,false);
    cfunc.plotData(CauchLorMet,100,false);
    crfunc.plotData(CrystalMet,100,false);

    //Bonus task was completed but has been left commented out as it increases runtime by alot
    //Ex34Functions piFunc ;
    //piFunc.PiFinder(1.0,100000);

    return 0;
}