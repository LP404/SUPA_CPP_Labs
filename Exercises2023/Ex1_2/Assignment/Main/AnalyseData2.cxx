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



///Custom power function that does not use a for loop or an inbuilt/imported power function

std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y);

std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y){

int n = x.size();
int count = 0;
std::vector<float> xyPow;

    while(count <= n){
        xyPow.push_back(exp(y[count] * log(x[count)));        
        count++;
    }

return xyPow;    
}


int printFunc2(const char* fmt...);
void printFunc2(const char* fmt...)
{
    va_list args;
    va_start(args, fmt);
 
    while (*fmt != '\0')
    {
        if (*fmt == 'v')
        {
            std::vector<float> vec = va_arg(args, std::vector<float>);
            
        }
        else if (*fmt == 'x')
        {
            // note automatic conversion to integral type
            std::vector<float> xVal = va_arg(args, std::vector<float>);
            int xAssign = 1;
        }
        else if (*fmt == 'y')
        {
            // note automatic conversion to integral type
            std::vector<float> yVal = va_arg(args, std::vector<float>);
            int yAssign = 1;
        }
        else if (*fmt == 'xErr')
        {
            // note automatic conversion to integral type
            std::vector<float> xValErr = va_arg(args, std::vector<float>);
            int xErrAssign = 1;
        }
        else if (*fmt == 'yErr')
        {
            // note automatic conversion to integral type
            std::vector<float> yValErr = va_arg(args, std::vector<float>);
            int yErrAssign = 1;
        }              
        else if (*fmt == 'f')
        {
            // note automatic conversion to integral type
            float boat = va_arg(args, float);
            std::cout << boat;
        }
        else if (*fmt == 's')
        {
            // note automatic conversion to integral type
            string strimples = va_arg(args, string);
        }
        else if (*fmt == 'nlin')
        {
            // note automatic conversion to integral type
            std::cout << "\n";
        }
        ++fmt;

    }
    
    if (xErrAssign == 1 and yErrAssign == 1){
        
        
    }
    
 
    va_end(args);

}
 


void printFunc2(const char* fmt...);
void printFunc2(const char* fmt...)
{
    va_list args;
    va_start(args, fmt);
 
    while (*fmt != '\0')
    {
        if (*fmt == 'd')
        {
            int i = va_arg(args, int);
            std::cout << i << '\n';
        }
        else if (*fmt == 'c')
        {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << '\n';
        }
        else if (*fmt == 'f')
        {
            double d = va_arg(args, double);
            std::cout << d << '\n';
        }
        ++fmt;
    }
 
    va_end(args);

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
    
std::cout << m << "\n" << c << "\n" << chiSq;

powXY = OwnPowFunc(x,y);


/// Printing some functions - 22/11/23

///printFunc(x,y,mag,7);


return 0;
}
