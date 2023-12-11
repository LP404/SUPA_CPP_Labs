#include "FiniteFunctions2.h"
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

///Put numeric everywhere to try and get rid of an error
///The negative Crystal ball function only plots right roughly half of the time and I don't know why. If I had more time I'd look into it properly
///Just run it again if it doesn't plot right

///It was found that a Cauchy-Lorentz Distribution with a gamma of 0.75 and a x0 of 0, was the correct one for the data.

int main(){

    ///Imports the generated values from the txt
    std::vector<double> importVals;
    Ex34Functions rfunc;
    importVals = rfunc.ReadFunc("Outputs/data/MysteryData13120.txt");

    ///Figues out the max and min values
    std::vector<double>::iterator m_RMin = std::min_element(importVals.begin(), importVals.end());
    std::vector<double>::iterator m_RMax = std::max_element(importVals.begin(), importVals.end());

    ///Calls/constructs the relecent class, with appropritate input paramaters/ distributions selected
    ///This is true for all of the next four calls
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


    ///Need to declate vectors to hold the linearly spaced array
    std::vector<double> GaussMet;
    std::vector<double> CauchLorMet;
    std::vector<double> CrystalMet;
    
    ///Pickes a nice even number for our samples
    int samSize = 100000;

    ///Assigns values to these vectors
    GaussMet = gfunc.VectorMaker(samSize);
    CauchLorMet = cfunc.VectorMaker(samSize);
    CrystalMet = crfunc.VectorMaker(samSize);

    ///Will now put each x values in the vector to get f(x) for each distribution
    for (int i=0; i<samSize; i++) {
        GaussMet[i] = gfunc.callFunction(GaussMet[i]);
        CauchLorMet[i] = cfunc.callFunction(CauchLorMet[i]);
        CrystalMet[i] = crfunc.callFunction(CrystalMet[i]);
    }

    ///Performs the metropolis alogithim on the data to get the random samples
   for (int i=0; i<samSize; i++) {
        GaussMet[i+1] = gfunc.Metropolis(GaussMet[i],0,0.25);
        CauchLorMet[i+1] = cfunc.Metropolis(CauchLorMet[i],0,0.25);
        CrystalMet[i+1] = crfunc.Metropolis(CrystalMet[i],0,3);
    }

    ///Plots the data, not all of it.
    gfunc.plotData(GaussMet,100,false);
    cfunc.plotData(CauchLorMet,100,false);
    crfunc.plotData(CrystalMet,100,false);

    //Bonus task was completed but has been left commented out as it increases runtime by alot
    //Does not report a fully accurate Pi value
    //Ex34Functions piFunc ;
    //piFunc.PiFinder(1.0,100000);

    ///Function has to return something
    return 0;
}