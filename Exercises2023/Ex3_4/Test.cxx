#include "FiniteFunctions.h"
#include <vector>


int main(){

    std::vector<double> importVals;
    importVals = ReadFunc("Outputs/data/MysteryData13120.txt");

    FiniteFunction func(-5,5,"Output");
    func.plotFunction();
    func.plotData(importVals,100);


    return 0;
}