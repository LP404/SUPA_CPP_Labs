// LP 15/11/23 Adding some numbers

#include <iostream>
#include <vector>
#include <cmath>

//Function for squaring a float
int squareNum(float valIn); //prototype

int squareNum(float valIn){ //def
    return (valIn*valIn);
}

int main(){

    //Declare variables
    float x = 2.3;
    float y = 4.5;

    //Do the monster math according to some vector properties
    float mag = sqrt((squareNum(x) + squareNum(y)));

    //Print
    std::cout << mag << std::endl;
    return 0;

}