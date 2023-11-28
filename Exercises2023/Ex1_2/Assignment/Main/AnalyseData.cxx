// LP 15/11/23
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cstdarg>
#include " CustomFunctions.h"

int main(){

///Declate me some vectors - 22/11/23

std::vector<float> x;
std::vector<float> y;

std::vector<float> xErr;
std::vector<float> yErr;

///I'm not exactly sure what auto does, but it works and I'm not ready to question it yet - 22/11/23
///Not exactly the mindset a scientist should have - 27/11/23
auto ret = ReadFunc("input2D_float.txt");
    x = ret.first;
    y = ret.second;
auto ret2 = ReadFunc("error2D_float.txt");
    xErr = ret2.first;
    yErr = ret2.second;


int userInput;
userInput = UserInputFunc(userInput);


switch (userInput) {
  case 0:
  {
    std::vector<float> mag;
    int n;

    std::cout << "How many values would you like to display and save?" << "\n" <<std::endl;
    std::cin >> n;

    mag = magCal(x,y);

    WriteFunc("MagFiles",x, y, mag, n,true);
    printFunc(x,y,mag,n,true);

    break;
  }
  
  case 1:
   {
    float m;
    float c;
    float chiSq;
    
    
    auto rawrXD = LsqFit(x,y,xErr,yErr);
        m = std::get<0>(rawrXD);
        c = std::get<1>(rawrXD);
        chiSq = std::get<2>(rawrXD);
        WriteFunc("lineFiles",m, c, chiSq);
        printFunc(m,c,chiSq);


    break;
   }
  
  case 2:
    {
    int n;
    std::vector<float> powXY;
    std::vector<float> out;
    std::cout << "How many values would you like to display and save?" << "\n" <<std::endl;
    std::cin >> n;
    powXY = OwnPowFunc(x,y,out,0);
    WriteFunc("powerXtoY",x, y, powXY, n,false);
    printFunc(x,y,powXY,n,false);
}
  case 3:
    {
    std::cout << "Script terminated" << "\n" <<std::endl;
    return 0;
}
}

return 0;
}