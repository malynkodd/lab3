#include "FuncA.h"
#include <cmath>
#include <vector>

// Function to return Bernoulli numbers based on the index provided
double FuncA::bernoulli(int index) {
   
    // Static vector of known Bernoulli numbers up to a certain index.
    static std::vector<double> bernoulliNumbers = {
        1, -0.5, 0.16666666666666666, 0, -0.03333333333333333, 0,
        0.023809523809523808, 0, -0.03333333333333333, 0, 0.07575757575757576
        // Add more Bernoulli numbers here if needed.
    };
    
    // Return the Bernoulli number at the specified index or 0 if index is out of range.
    return (index < bernoulliNumbers.size()) ? bernoulliNumbers[index] : 0;
}

// Function to calculate a trigonometric sum based on the input 'n' and 'x' values
double FuncA::calculateTrigFunction(int n, double x) {
    double sum = 0;
    
    // Loop through terms up to 'n' to accumulate the series sum
    for (int k = 1; k <= n; ++k) {
        // The index for Bernoulli numbers is 2*k (only even indices are used)
        int index = 2 * k; 
        
        // Get the corresponding Bernoulli number for the current term
        double bernoulliNumber = bernoulli(index);
        
        // Calculate the term in the series using the Bernoulli number and other parameters
        double term = (bernoulliNumber * pow(-4, k) * (1 - pow(4, k)) * pow(x, 2 * k - 1)) / tgamma(2 * k + 1);
        
        // Add the calculated term to the sum
        sum += term;
    }
    
    // Return the accumulated sum as the result of the trigonometric calculation
    return sum;
}
