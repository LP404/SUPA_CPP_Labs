// LP 15/11/23

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(){

std::ifstream myInput("input2D_float.txt");

if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    return 0;
}

float x,y;
std::string strHold;
std::string line;

bool FirstInstance = true;
while(getline(myInput,line)){
    //The loop will 'discard' the string values
    if (FirstInstance == true){
        getline(myInput,line);
        FirstInstance = false;
    }
    std::stringstream findLine(line);
    getline(findLine,strHold,',');
    x = std::stof(strHold);
    getline(findLine,strHold,',');
    y = std::stof(strHold);
    std::cout<<x<<" "<<y<<std::endl;
}

myInput.close();

return 0;
}