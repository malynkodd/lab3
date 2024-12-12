#include "FuncA.h"
#include <cmath>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdio>
#include <iostream>


void FuncA::serverimulation() {

    // Змінна для зберігання часу
    char strTimeEllapsed[20];
    
    // Початок вимірювання часу
    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<double> aValues;
    FuncA func;

    const int n = 5; // Number of terms in the series
    const double xStart = 0.0; // Starting value for calculations
    const int arraySize = 2000000; // Number of elements in the array

    for (int i = 0; i < arraySize; i++) {
        double x = xStart + i * 0.0001; // Increment x slightly for each value
        aValues.push_back(func.calculateTrigFunction(n, x));
    }

    // Сортування вектора
    for (int i = 0; i < 500; i++) {
        sort(aValues.begin(), aValues.end());
        reverse(aValues.begin(), aValues.end());
    }

    // Кінець вимірювання часу
    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    // Отримуємо значення часу в мілісекундах
    int iMS = int_ms.count();

    // Перетворюємо час в рядок
    sprintf(strTimeEllapsed, "%d ms", iMS);

    // Виводимо час
    std::cout << "Elapsed time: " << strTimeEllapsed << std::endl;
}





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
