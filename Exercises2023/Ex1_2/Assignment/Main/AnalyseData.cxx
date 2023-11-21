// LP 15/11/23

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// Function will read a two colum txt file, it will also discard the first line
float ReafFunc(str fileName){

std::ifstream myInput(fileName);

if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    return 0;
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


    return x,y;
}


str printFunc(float x, float y, int n){

///We can safely assume in this case that each x will have a corresponding y value
///If not then I have to do better input checking

if (n > x.size() and n < 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing all avliable lines"<<std::endl;

    for (int i = 0; i < n; i++){

        std::cout<<"Printing all avliable lines"<< x.[0] <<std::endl;
        std::cout<<"Printing all avliable lines"<<std::endl;

    }

}

else if(n > x.size() and n >= 5){
    std::cout<<"Warning! Number of values selected is greater than number of values avaliable"<<std::endl;
    std::cout<<"Printing first five lines."<<std::endl;




}

else{




}
    std::cout<<xHold<<" "<<yHold<<std::endl;
}


int main(){

"input2D_float.txt"



}

myInput.close();

return 0;
}