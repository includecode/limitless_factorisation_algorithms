#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include "Factoriser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    unsigned long long int nbre;
    /*
    std::cout << "Entrer le nombre à factoriser:";
    
    cin >> nbre;
    */
    if (argc != 2)
    {
        cout << "---------FACTORISATION DES GRANDS NOMBRES------" << endl;
        cout << " Pour utiliser ce programme, veuillez entrer un nombre à factoriser." << endl;
        cout << "\tExemple:    ./app 1000      (pour factoriser le nombre 1000)" << endl;
        cout << "------FIN DU PROGRAMME-----" << endl;
        cout << "Par: Pavel SAMENE TIAH (c) Novembre 2019" << endl;
        cout << "<pavelhilson@gmail.com>" << endl;
    }
    else
    {

        nbre = atoi(argv[1]);

        Factoriser *testFactorisationNaive = new Factoriser(nbre);
        std::cout << "--------------------------" << endl;
        std::cout << "DEBUT FACTORISATION NAIVE" << endl;

        clock_t beginNative = clock();
        testFactorisationNaive->factorisationNaive(nbre);
        clock_t endNative = clock();
        testFactorisationNaive->printFactorsResult();
        std::cout << "FIN FACTORISATION NAIVE" << endl;
        std::cout << "--------------------------" << endl;
        /*
    Factoriser *factorisationFermat = new Factoriser(nbre);
    std::cout << endl;
    std::cout << "DEBUT FACTORISATION FERMAT" << endl;
    clock_t beginFermat = clock();
    factorisationFermat->fermatFactorisation(nbre);
    clock_t endFermat = clock();
    factorisationFermat->printFactorsResult();
    std::cout << "FIN FACTORISATION FERMAT" << endl;
    std::cout << "--------------------------" << endl;
*/
        unsigned long long int borne = 2;
        unsigned long long int a = 2;
        Factoriser *factorisationPollard = new Factoriser(nbre);
        std::cout << endl;
        std::cout << "DEBUT FACTORISATION POLLARD -1" << endl;
        clock_t beginPollardMinusOne = clock();
        factorisationPollard->recurvivePollardMinusOne(nbre, borne, a);
        clock_t endPollardMinusOne = clock();
        std::cout << "FIN FACTORISATION POLLARD -1" << endl;
        factorisationPollard->printFactorsResult();

        double time_spent_native = (double)(endNative - beginNative) / CLOCKS_PER_SEC;
        //double time_spent_fermat = (double)(endFermat - beginFermat) / CLOCKS_PER_SEC;
        double time_spent_PollardMinusOne = (double)(endPollardMinusOne - beginPollardMinusOne) / CLOCKS_PER_SEC;
        cout << "Native function   = " << time_spent_native << " seconds" << endl;
        //  cout << "Fermat function   = " << time_spent_fermat << " seconds" << endl;
        cout << "Pollard function  = " << time_spent_PollardMinusOne << " seconds" << endl;

        ofstream myfile;
        myfile.open("resultNaive.txt", std::fstream::app);
        myfile <<time_spent_native<< "\n";
        myfile.close();

        myfile.open("resultPollard.txt", std::fstream::app);
        myfile <<time_spent_PollardMinusOne<< "\n";
        myfile.close();

        myfile.open("testedNumbers.txt", std::fstream::app);
        myfile <<nbre<< "\n";
        myfile.close();

        //Séparer factorisationNaive() en deux fonctions, il faut celle qui renvoie true/false si le nombre est premier
    }
    return 0;
}