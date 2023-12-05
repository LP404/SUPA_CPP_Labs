#include <string>
#include <vector>
#include <tuple>

///.h file
///Creates protoypes for each of the functions used in the main()

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
