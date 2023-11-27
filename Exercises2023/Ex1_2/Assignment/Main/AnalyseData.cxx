// LP 15/11/23

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include <cstdarg>

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

int WriteFunc(std::string fName,std::vector<float> x, std::vector<float> y, std::vector<float> result);


int WriteFunc(std::string fName,std::vector<float> x, std::vector<float> y, std::vector<float> result){
}




int WriteFunc(std::string fName,float m, float c, float chiSq);


int WriteFunc(std::string fName,float m, float c, float chiSq){
}










int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> mag,int n);

int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> mag, int n){


///We can safely assume in this case that each x will have a corresponding y value - 15/11/23?
///If not then I have to do better input checking - 15/11/23?

if (n > x.size() and n < 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<< "\n" << std::endl;
    std::cout<<"Printing all avaliable lines"<< "\n" <<std::endl;

    for (int i = 0; i < n; i++){

        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude"<< mag[i] << "\n" <<std::endl;


    }

}

else if(n > x.size() and n <= 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<< "\n" <<std::endl;
    std::cout<<"Printing first five coordiante pairs."<< "\n" <<std::endl;

    for (int i = 0; i < 5; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude"<< mag[i] << "\n" <<std::endl;

    }

}

else{
    std::cout<<"Printing " << n << " coordiante pairs."<< "\n" << std::endl;
    for (int i = 0; i < n; i++){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude : "<< mag[i] << "\n" <<std::endl;

    }


}
return 0;
}

int printFunc(std::vector<float> x,std::vector<float> y,std::vector<float> xyPow);

int printFunc(std::vector<float> x,std::vector<float> y,std::vector<float> xyPow){

    int n = xyPow.size();

    for (int i = 0; i < n; i++){
        std::cout << "The result of: "<< x[i] << " to the power of " << y[i] << " is: "<< xyPow[i] << "\n" <<std::endl;
    }


return 0;
}

int printFunc(float m,float c,float chiSq);

int printFunc(float m,float c,float chiSq){

    std::cout<< "The gradient is : " << m << "\n" << std::endl;
    std::cout<< "The y-intercept is : " << c << "\n" << std::endl;
    std::cout<< "This fit has a Chi Squared / NDF value of : " << chiSq << "\n" << std::endl;

return 0;
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

std::tuple<float, float, float>  LsqFit(std::vector<float> x, std::vector<float> y, std::vector<float> xErr, std::vector<float> yErr);

std::tuple<float, float, float>  LsqFit(std::vector<float> x, std::vector<float> y, std::vector<float> xErr, std::vector<float> yErr){

float m,c;
int n = x.size();
float N = static_cast<float>(x.size());

float sumX = 0.0;
float sumY = 0.0;
float sumXY = 0.0;
float sumXsq = 0.0;
std::vector<float> yFit;
float chiSq = 0.0;


///We can assume that for each x there will be a y, so we can do all the calcualtions in one loop
for(int i = 0; i < n; i++){
     sumX += x[i];
     sumY += y[i];
     sumXY += (x[i] * y[i]);
     sumXsq += pow(x[i],2);
}


m = ((N*sumXY) - (sumX*sumY)) / ((N*sumXsq) - (pow(sumX,2)));
c = ((sumXsq*sumY) - (sumXY*sumY)) / ((N*sumXsq) - (pow(sumX,2)));

for(int i = 0; i < n; i++){
    yFit.push_back(((m*x[i]) + c));
}


///kind of assuming that the inputs and error have the same dimentions
for(int i = 0; i < n; i++){
    chiSq += pow((yFit[i]-y[i]),2) / (pow(yErr[i],2));
}

chiSq = chiSq/(N-2.0);

return std::tuple<float, float, float>{m, c, chiSq};
}

///Custom power function that does not use a loop or an inbuilt/imported power function
///Honestly looking at this makes me sick

std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y,std::vector<float> out,int count);

std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y,std::vector<float> out,int count){


if(count < x.size()){
    out.push_back(exp(y[count] * log(x[count])));   
    return OwnPowFunc(x,  y, out, count+1);  
}

else{
    return out;
}

}






int main(){

///Declate me some vectors - 22/11/23

std::vector<float> x;
std::vector<float> y;

std::vector<float> xErr;
std::vector<float> yErr;


float m;
float c;
float chiSq;
std::vector<float> mag;
std::vector<float> powXY;
///I'm not exactly sure what auto does, but it works and I'm not ready to question it yet - 22/11/23

auto ret = ReadFunc("input2D_float.txt");
    x = ret.first;
    y = ret.second;

auto ret2 = ReadFunc("error2D_float.txt");
    xErr = ret2.first;
    yErr = ret2.second;

mag = magCal(x,y);

auto rawrXD = LsqFit(x,y,xErr,yErr);
    m = std::get<0>(rawrXD);
    c = std::get<1>(rawrXD);
    chiSq = std::get<2>(rawrXD);
    
std::vector<float> out;

powXY = OwnPowFunc(x,y,out,0);


/// Printing some functions - 22/11/23





return 0;
}