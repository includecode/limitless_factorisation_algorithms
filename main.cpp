#include <iostream>
#include <cmath>
#include <chrono>
#include "Factoriser.hpp"
using namespace std;

int main(int argc, char *argv[])
{

    //DecimalToBinary(1844674407370955161);
    /*
    clock_t begin = clock();

    // Get ending timepoint
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken by function: "
         << time_spent << " seconds" << endl;
         */
    std::cout << "Entrer le nombre à factoriser:";
    unsigned long long int nbre;
    cin >> nbre;
    Factoriser *factorisationNaive = new Factoriser(nbre);
    std::cout << "--------------------------" << endl;
    std::cout << "DEBUT FACTORISATION NAIVE" << endl;
    factorisationNaive->factorisationNaive(nbre);
    factorisationNaive->printFactorsResult();
    std::cout << "FIN FACTORISATION NAIVE" << endl;
    std::cout << "--------------------------" << endl;

    Factoriser *factorisationFermat = new Factoriser(nbre);
    std::cout << endl;
    std::cout << "DEBUT FACTORISATION FERMAT" << endl;
    factorisationFermat->fermatFactorisation(nbre);
    factorisationFermat->printFactorsResult();
    std::cout << "FIN FACTORISATION FERMAT" << endl;
    std::cout << "--------------------------" << endl;
    return 0;
}