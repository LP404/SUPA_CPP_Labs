#include "FiniteFunctions.h"
#include <vector>

std::vector<double> ReadFunc(std::string fName);

std::vector<double> ReadFunc(std::string fName){

///Opens a file, ready for reading in data
std::ifstream myInput(fName);

///Checks if this file is open, terminates function if that is not the case. Notifies user
if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    exit(1);
}

///Initilises variables that will be used to store data
double valHold;
std::vector<double> val;
std::string strHold;
std::string line;

///Reads in each data from each line, seperated by the comma
///The first loop will read in data but not assign the strings to anything
///Appends data to two vectors, while converting the string it reads in, to a float
while(getline(myInput,line)){
    //The loop will 'discard' the string values
    std::stringstream findLine(line);
    getline(findLine,strHold);
    val.push_back(std::stod(strHold));
}

///Closes the file and returns values out of the fucntion
myInput.close();
return val;
}



int main(){

    std::vector<double> importVals;
    importVals = ReadFunc("Outputs/data/MysteryData13120.txt");

    FiniteFunction func(-5,5,"Output");
    func.plotFunction();


    return 0;
}