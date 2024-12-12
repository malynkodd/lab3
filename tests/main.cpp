#include "../FuncA.h"
#include <iostream>
#include <cmath>


bool verifyTrigSum(int n, double x, double expected_result) {
    FuncA func;
    double result = func.calculateTrigFunction(n, x);

    double tolerance = 1; 
    return std::abs(result - expected_result) < tolerance;
}

int main() {
    // Вхідні параметри
    double x = M_PI / 4; 
    int n = 5;           

    
    double expected_result = x 
                            - (std::pow(x, 3) / 6) 
                            + (std::pow(x, 5) / 120); 

   
    if (verifyTrigSum(n, x, expected_result)) {
        std::cout << "The trigonometric series sum is correct!" << std::endl;
        return 0; 
    } else {
        std::cout << "The trigonometric series sum is incorrect!" << std::endl;
        return 1; 
    }
}



