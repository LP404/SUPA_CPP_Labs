// LP 15/11/23 Adding some numbers

#include <iostream>
#include <vector>
#include <cmath>

int main(){

    //Declare variables
    float x = 2.3;
    float y = 4.5;

    //Do the monster math according to some vector properties
    float mag = sqrt((pow(x,2) + pow(y,2)));

    //Print
    std::cout << "The vector length is " << mag << std::endl;
    return 0;

}