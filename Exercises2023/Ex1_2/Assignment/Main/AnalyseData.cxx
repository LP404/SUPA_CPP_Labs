// LP 15/11/23

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Function cannot output more than one variable

std::pair<std::vector<float>, std::vector<float>> ReadFunc(std::string fName);

/// Function will read a two colum txt file, it will also discard the first line
std::pair<std::vector<float>, std::vector<float>> ReadFunc(std::string fName){

std::ifstream myInput(fName);

if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    exit(1);
}

float xHold,yHold;
std::vector<float> x,y;
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
    x.push_back(std::stof(strHold));
    getline(findLine,strHold,',');
    y.push_back(std::stof(strHold));
}

myInput.close();
return {x,y};
}

int printFunc(std::vector<float> x, std::vector<float> y, int n);

int printFunc(std::vector<float> x, std::vector<float> y, int n){


///We can safely assume in this case that each x will have a corresponding y value
///If not then I have to do better input checking

if (n > x.size() and n < 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing all avaliable lines"<<std::endl;

    for (int i = 0; i < n; i++){

        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ")"<<std::endl;


    }

}

else if(n > x.size() and n <= 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing first five coordiante pairs."<<std::endl;

    for (int i = 0; i < 5; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ")"<<std::endl;

    }

}

else{
    std::cout<<"Printing " << n << " coordiante pairs."<<std::endl;
    for (int i = 0; i < n; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ")"<<std::endl;

    }




}
return 0;
}


int main(){

///Declate me some vectors

std::vector<float> x;
std::vector<float> y;

///I'm not exactly sure what auto does, but it works and I'm not ready to question it yet

auto ret = ReadFunc("input2D_float.txt");
    x = ret.first;
    y = ret.second;

/// Printing some functions


printFunc(x,y, 7);



return 0;
}




