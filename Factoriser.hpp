#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
class Factoriser
{
private:
    unsigned long long int number;
    unsigned long long int *factorisationResult;
    int countResults;

public:
    Factoriser(unsigned long long int number);
    unsigned int squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d);
    void fermatFactorisation(unsigned long long int n);
    void factorisationNaive(unsigned long long int nbre);
    short int *DecimalToBinary(unsigned long long int n);
    bool isSquare(unsigned long long int n);
    void addNewFactorToResult(unsigned long long int result);
    void printFactorsResult();

    //Getters and setters
    void setNumber(unsigned long long int number);
    unsigned long long int getNumber();
    int getCountResults();
    void setCountResults(int countResults);
};
#endif