#include <cmath> 
#include "FuncA.h"
#include <iostream>

int main() {
    FuncA func; 
    int n;
    double x;

    std::cout << "Введіть кількість елементів n: ";
    std::cin >> n;
    std::cout << "Введіть значення x (|x| < pi/2): ";
    std::cin >> x;

    const double PI = 3.14159265358979323846;

    if (std::abs(x) >= PI / 2) { 
        std::cout << "Помилка: значення x має бути менше за pi/2" << std::endl;
        return 1;
    }

    // Use the correct function signature from branchA
    double result = func.calculateTrigFunction(n, x);
    std::cout << "Результат обчислення: " << result << std::endl;

    return 0;
}
