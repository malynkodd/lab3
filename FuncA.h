#ifndef FUNCA_H
#define FUNCA_H

/**
 * Class FuncA to calculate a trigonometric series.
 * 
 * @param n Number of terms to include in the series.
 */
class FuncA {
public:
    /**
     * Calculates the sum of the first `n` terms of an infinite series.
     * @param n Number of terms in the series.
     * @return Sum of the first `n` terms.
     */
    double calculateTrigFunction(int n, double x);
    double bernoulli(int index);
};

#endif // FUNCA_H
