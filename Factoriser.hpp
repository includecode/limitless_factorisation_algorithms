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
    unsigned int squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d, short int nbreRepeat);
    void fermatFactorisation(unsigned long long int n);
    void factorisationNaive(unsigned long long int nbre);
    short int *DecimalToBinary(unsigned long long int n);
    bool isSquare(unsigned long long int n);
    void addNewFactorToResult(unsigned long long int result);
    void printFactorsResult();

    //Pollard -1
    unsigned long long int pollardMinusOne(unsigned long long int nbre, unsigned long long int borne, unsigned long long int a);
    void recurvivePollardMinusOne(unsigned long long int nbre, unsigned long long int borne, unsigned long long int a);
    unsigned long long int factorielle(unsigned long long int nbre);
    unsigned long long int pgcd(unsigned long long int a, unsigned long long int b);

    //Getters and setters
    void setNumber(unsigned long long int number);
    unsigned long long int getNumber();
    int getCountResults();
    void setCountResults(int countResults);
};
#endif