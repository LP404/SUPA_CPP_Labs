// Lewis Penman - University of Strathclyde SUPA COO

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "CustomFunctions.h"

///Start Main
int main(){

///Declare vectors that will be used in every switch case

std::vector<float> x;
std::vector<float> y;

std::vector<float> xErr;
std::vector<float> yErr;

///I'm not exactly sure what auto does, but it works and I'm not ready to question it yet - 22/11/23
///Not exactly the mindset a scientist should have - 27/11/23

///Calls the readfunc and assigns outputs to the vectors
auto ret = ReadFunc("input2D_float.txt");
    x = ret.first;
    y = ret.second;
auto ret2 = ReadFunc("error2D_float.txt");
    xErr = ret2.first;
    yErr = ret2.second;


///Prompts user with what they want to do
///Will only accept a set number of values
int userInput;
userInput = UserInputFunc(userInput);

///Switch case statment is activated based on user input
switch (userInput) {
  ///Case 0 will calcualte and output vector magnitude
  case 0:
  {
    ///Initalises variable/vector
    std::vector<float> mag;
    int n;

    ///Prompts user for number of values
    ///I attemped input validation on this but it kept breaking depending on what input I was attempting to screen out
    std::cout << "How many values would you like to display and save?" << "\n" <<std::endl;
    std::cin >> n;

    ///Calls the magnitude calculation function and assigns output to vector
    mag = magCal(x,y);

    ///Prints and outputs data
    WriteFunc("MagFiles",x, y, mag, n,true);
    printFunc(x,y,mag,n,true);

    break;
  }
  
  ///Case 1 will perform least square fit and chiSq/NDF calculations
  case 1:
   {
    ///Initalises floats
    float m;
    float c;
    float chiSq;
    
    ///Calls the Lease Sqaure Fit calculation function and assigns output to float values
    auto rawrXD = LsqFit(x,y,xErr,yErr);
        m = std::get<0>(rawrXD);
        c = std::get<1>(rawrXD);
        chiSq = std::get<2>(rawrXD);

        ///Prints and outputs data
        WriteFunc("lineFiles",m, c, chiSq);
        printFunc(m,c,chiSq);


    break;
   }
  
  ///Case 2 will calcualte and output x^y
  case 2:
    {
    ///Initalises variable/vectors
    int n;
    std::vector<float> powXY;
    std::vector<float> out;

    ///Prompts user for number of values
    std::cout << "How many values would you like to display and save?" << "\n" <<std::endl;
    std::cin >> n;
    
    ///Calls the x^y calculation function and assigns output to vector
    powXY = OwnPowFunc(x,y,out,0);
    
    ///Prints and outputs data
    WriteFunc("powerXtoY",x, y, powXY, n,false);
    printFunc(x,y,powXY,n,false);
    break;
}
  ///Case 3 terminate the script
  case 3:
    {
    
    std::cout << "Script terminated by order of the La-Li-Lu-Le-Lo" << "\n" <<std::endl;
    break;
}
}
///Returns an int value of 0
return 0;
}