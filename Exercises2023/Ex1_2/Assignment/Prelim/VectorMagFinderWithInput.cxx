// LP 15/11/23 Adding some numbers

#include <iostream>
#include <vector>
#include <cmath>

int main(){

    //Declare variables

    float x;
    std::cout << "Please specify x value" << std::endl;
    std::cin >> x;


    float y;
    std::cout << "Please specify y value" << std::endl;
    std::cin >> y;
    
    //Do the monster math according to some vector properties
    float mag = sqrt((pow(x,2) + pow(y,2)));

    //Print
    std::cout << "The vector length is " << mag << std::endl;
    return 0;

}