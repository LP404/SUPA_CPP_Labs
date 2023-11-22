// LP 15/11/23

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

/// Function cannot output more than one variable - 21/11/23
///IT CAN NOW!!! HAHAHAHA - 22/11/23

std::pair<std::vector<float>, std::vector<float>> ReadFunc(std::string fName);

/// Function will read a two colum txt file, it will also discard the first line - 21/11/23
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


std::vector<float> magCal(std::vector<float> x, std::vector<float> y);

std::vector<float> magCal(std::vector<float> x, std::vector<float> y){

std::vector<float> mag;

int n;

n = x.size();

///Using pow because x*x was behaving weird and this was just the simpler optio

for (int i = 0; i < n; i++){
     mag.push_back(sqrt((pow(x[i],2) + pow(y[i],2))));
}

return mag;
}








int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> mag,int n);

int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> mag, int n){


///We can safely assume in this case that each x will have a corresponding y value - 15/11/23?
///If not then I have to do better input checking - 15/11/23?

if (n > x.size() and n < 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing all avaliable lines"<<std::endl;

    for (int i = 0; i < n; i++){

        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude"<< mag[i] <<std::endl;


    }

}

else if(n > x.size() and n <= 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing first five coordiante pairs."<<std::endl;

    for (int i = 0; i < 5; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude"<< mag[i] <<std::endl;

    }

}

else{
    std::cout<<"Printing " << n << " coordiante pairs."<<std::endl;
    for (int i = 0; i < n; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude : "<< mag[i] <<std::endl;

    }




}
return 0;
}





std::pair<float, float>  LsqFit(std::vector<float> x, std::vector<float> y);

std::pair<float, float>  LsqFit(std::vector<float> x, std::vector<float> y){

float m,c;
int n = x.size();
float N = static_cast<float>(x.size());

float sumX = 0.0;
float sumY = 0.0;
float sumXY = 0.0;
float sumXsq = 0.0;

///We can assume that for each x there will be a y, so we can do all the calcualtions in one loop
for(int i = 0; i < n; i++){
     sumX += x[i];
     sumY += y[i];
     sumXY += (x[i] * y[i]);
     sumXsq += pow(x[i],2);
}

m = ((N*sumXY) - (sumX*sumY)) / ((N*sumXsq) - (pow(sumX,2)));
c = ((sumXsq*sumXY) - (sumXY*sumY)) / ((N*sumXsq) - (pow(sumX,2)));

return {m,c};
}



int main(){

///Declate me some vectors - 22/11/23

std::vector<float> x;
std::vector<float> y;
float m;
float c;
std::vector<float> mag;
///I'm not exactly sure what auto does, but it works and I'm not ready to question it yet - 22/11/23

auto ret = ReadFunc("input2D_float.txt");
    x = ret.first;
    y = ret.second;

mag = magCal(x,y);
auto rawrXD = LsqFit(x,y);
    m = rawrXD.first;
    c = rawrXD.second;

/// Printing some functions - 22/11/23

///printFunc(x,y,mag,7);


return 0;
}



