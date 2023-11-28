#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include <cstdarg>

#pragma once
std::pair<std::vector<float>, std::vector<float>> ReadFunc(std::string fName);

#pragma once
int WriteFunc(std::string fName,std::vector<float> x, std::vector<float> y, std::vector<float> result, int n, bool isMag);

#pragma once
int WriteFunc(std::string fName,float m, float c, float chiSq);

#pragma once
int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> result,int n, bool isMag);

#pragma once
int printFunc(float m,float c,float chiSq);

#pragma once
std::vector<float> magCal(std::vector<float> x, std::vector<float> y);

#pragma once
std::tuple<float, float, float>  LsqFit(std::vector<float> x, std::vector<float> y, std::vector<float> xErr, std::vector<float> yErr);

#pragma once
std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y,std::vector<float> out,int count);

#pragma once
int UserInputFunc(int userInput);