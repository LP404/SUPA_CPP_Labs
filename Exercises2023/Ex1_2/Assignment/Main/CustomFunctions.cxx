#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include <cstdarg>

///Note: I think I've been extensive with the comments, please tell me if this is too much or too little
///Also before we begin, I must say that almost every function coded with the assumption that for each x value, that there is a corresponding y value

///Function will read a two column txt file, it will also discard the first line
///Takes a filename as an input and will output a 'pair' of vectors
std::pair<std::vector<float>, std::vector<float>> ReadFunc(std::string fName){

///Opens a file, ready for reading in data
std::ifstream myInput(fName);

///Checks if this file is open, terminates function if that is not the case. Notifies user
if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    exit(1);
}

///Initilises variables that will be used to store data
float xHold,yHold;
std::vector<float> x,y;
std::string strHold;
std::string line;

///Reads in each data from each line, seperated by the comma
///The first loop will read in data but not assign the strings to anything
///Appends data to two vectors, while converting the string it reads in, to a float
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

///Closes the file and returns values out of the fucntion
myInput.close();
return {x,y};
}

///Function will create and write to a txt file
///Takes a filename as an input, along with the required vectors, number of times it should write data and a boolean variable that
///will adjust the output depending on what operation is being performed.
///'Returns' a txt file. Actually returns 0, which is unassigned
int WriteFunc(std::string fName,std::vector<float> x, std::vector<float> y, std::vector<float> result , int n ,bool isMag){

///Creates a file with specifed name input
std::ofstream myOutput (fName+".txt");

///Checks if this file is open, terminates function if that is not the case. Notifies user 
if(!myOutput.is_open()){
    std::cout<<"File could not opened"<<std::endl;
    exit(1);
}

///Creates first line with column titles based on boolean value
if(isMag == true){
    myOutput << "x,y,mag" << "\n";
}
else{
    myOutput << "x,y,powerXtoY"<< "\n";
}

///Writes the data to the txt for n lines in a format similar to the provided .txts in this excersise.  
for (int i = 0; i < n; i++){
    myOutput << x[i] << "," << y[i] << "," << result[i]<<"\n";
  }

///Closes the file and returns values out of the fucntion
myOutput.close();
return 0;
}

///Oveload function, solely for fit paramaters task
///Function will create and write to a txt file
///Takes a filename as an input, along with the required floats
///'Returns' a txt file. Actually returns 0, which is unassigned
int WriteFunc(std::string fName,float m, float c, float chiSq){

///Creates a file with specifed name input
std::ofstream myOutput (fName+".txt");

///Checks if this file is open, terminates function if that is not the case. Notifies user 
if(!myOutput.is_open()){
    std::cout<<"File could not opened"<<std::endl;
    exit(1);
}

///Note m is p; and q is c
///Writes the data to the txt for n lines in a format similar to the provided .txts in this excersise.  
myOutput << "m,c,chiSq"<< "\n";
myOutput << m<< ","<< c << "," << chiSq<< "\n";

///Closes the file and returns values out of the fucntion
myOutput.close();
return 0;
}


///Function will print data to terminal
///Takes required vectors, number of times it should write data, and a boolean variable that will adjust the output depending on what operation is being performed
///'Returns' printouts to the terminal. Actually returns 0, which is unassigned
int printFunc(std::vector<float> x, std::vector<float> y, std::vector<float> result, int n, bool isMag){


///We can safely assume in this case that each x will have a corresponding y value - 15/11/23?
///If not then I have to do better input checking - 15/11/23?

///Performs the check that if more values are being asked for than exist, then it will only print five values 
///BUT if less than five values exist, then it will print out all values instead
///The bool variable will adjust the printout for the different cases of user input
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

///Performs the check that if more values are being asked for than exist, then it will only print five values 
///The bool variable will adjust the printout for the different cases of user input
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

///For a n value less than or equal to the number of existing values it will simply printout n values
///The bool variable will adjust the printout for the different cases of user input
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

///Returns 0 to end function
return 0;
}


///Printfunc overload for the line fit paramers task
///'Returns' printouts to the terminal. Actually returns 0, which is unassigned
int printFunc(float m,float c,float chiSq){

    std::cout<< "The gradient is: " << m << "\n" << std::endl;
    std::cout<< "The y-intercept is: " << c << "\n" << std::endl;
    std::cout<< "This fit has a Chi Squared / NDF value of: " << chiSq << "\n" << std::endl;

///Returns 0 to end function
return 0;
}

///Calculates the magnitiude of vectors assuming their origin is (0,0) and their endpoint is the coordiantes listed in the input
///Takes in two vectors of floats as an input
///Will return a vector of floats
std::vector<float> magCal(std::vector<float> x, std::vector<float> y){

///Initalises the output vector of floats
std::vector<float> mag;

///Initalises the n values as an int
int n = x.size();

///Using pow because x*x was behaving weird and this was just the simpler option - old
///It may work just as well with x*x but it works and I see no reason to change it in this instance
///Will do a simple vector magnitide calculation then push back each value to the end of the vector
for (int i = 0; i < n; i++){
     mag.push_back(sqrt((pow(x[i],2) + pow(y[i],2))));
}

///Returns the output vector
return mag;
}

///Performs the least sqaure fit and chiSq/NDF calcualtion
///Takes in requied vectors to perform the calculation
///Will output a tuple that consists of the three desired values
std::tuple<float, float, float>  LsqFit(std::vector<float> x, std::vector<float> y, std::vector<float> xErr, std::vector<float> yErr){

///Initilises all of the requied variables
float m,c;
int n = x.size();

///This is requied as we need the same datatypes (int/float. I am aware that there are
///different forms of int and float, but I believe that they are compatable wit eachtoher
///in C++) present in a numerical operation in order for it to run.
float N = static_cast<float>(x.size());

///Initilising more variables, and assigning some inital values of 0
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