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

int WriteFunc(std::string fName,std::vector<float> x, std::vector<float> y, std::vector<float> result , int n ,bool isMag){

std::ofstream myOutput (fName+".txt");
  
if(!myOutput.is_open()){
    std::cout<<"File could not opened"<<std::endl;
    exit(1);
}

if(isMag == true){
    myOutput << "x,y,mag" << "\n";
}
else{
    myOutput << "x,y,powerXtoY"<< "\n";
}

for (int i = 0; i < n; i++){
    myOutput << x[i] << "," << y[i] << "," << result[i]<<"\n";
  }
myOutput.close();
return 0;


}


int WriteFunc(std::string fName,float m, float c, float chiSq){

std::ofstream myOutput (fName+".txt");
  
if(!myOutput.is_open()){
    std::cout<<"File could not opened"<<std::endl;
    exit(1);
}

///Note m is p; and q is c
myOutput << "m,c,chiSq"<< "\n";
myOutput << m<< ","<< c << "," << chiSq<< "\n";
myOutput.close();
return 0;


}



int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> result, int n, bool isMag){


///We can safely assume in this case that each x will have a corresponding y value - 15/11/23?
///If not then I have to do better input checking - 15/11/23?

if (n > x.size() and n < 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<< "\n" << std::endl;
    std::cout<<"Printing all avaliable lines"<< "\n" <<std::endl;

    for (int i = 0; i < n; i++){

        if (isMag == true){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude: "<< result[i] << "\n" <<std::endl;
        }
        else{
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with x^y value of: "<< result[i] << "\n" <<std::endl;
        }

    }

}

else if(n > x.size() and n <= 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<< "\n" <<std::endl;
    std::cout<<"Printing first five coordiante pairs."<< "\n" <<std::endl;

    for (int i = 0; i < 5; i++){
        if (isMag == true){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude: "<< result[i] << "\n" <<std::endl;
        }
        else{
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with x^y value of: "<< result[i] << "\n" <<std::endl;
        }
    }

}

else{
    std::cout<<"Printing " << n << " coordiante pairs."<< "\n" << std::endl;
    for (int i = 0; i < n; i++){
        if (isMag == true){
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ") with magnitude: "<< result[i] << "\n" <<std::endl;
        }
        else{
        std::cout << "Coordiante pair: "<< i+1 << " (" << x[i] << "," << y[i] << ")  with x^y value of: "<< result[i] << "\n" <<std::endl;    
        }
    }


}
return 0;
}

int printFunc(float m,float c,float chiSq){

    std::cout<< "The gradient is: " << m << "\n" << std::endl;
    std::cout<< "The y-intercept is: " << c << "\n" << std::endl;
    std::cout<< "This fit has a Chi Squared / NDF value of: " << chiSq << "\n" << std::endl;

return 0;
}

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


std::vector<float>  OwnPowFunc(std::vector<float> x, std::vector<float> y,std::vector<float> out,int count){


if(count < x.size()){
    out.push_back(exp(y[count] * log(x[count])));   
    return OwnPowFunc(x,  y, out, count+1);  
}

else{
    return out;
}

}


int UserInputFunc(int userInput){
    std::cout << "What function would you like to run?" << "\n" <<std::endl;
    std::cout << "Find vector magnitude and; print and save n values (0)" << "\n" <<std::endl;
    std::cout << "Find line of best fit via least square fitting (1)" << "\n" <<std::endl;
    std::cout << "Find the result of x^y and; print and save n values (2)" << "\n" <<std::endl;
    std::cout << "Terminate script (3)" << "\n" <<std::endl;
    std::cin >> userInput;
    std::cout << "\n" <<std::endl;
    if(userInput !=0 and userInput !=1 and userInput !=2 and userInput !=3){
        std::cout << "Invalid response, please type 0, 1, 2, or 3" << "\n" <<std::endl;
        UserInputFunc(userInput);
    }
    else{
    return userInput;
    }
}

int main()
{
return 0;
}