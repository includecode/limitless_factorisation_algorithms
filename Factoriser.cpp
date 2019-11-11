#include <iostream>
#include <cmath>
#include <chrono>
#include "Factoriser.hpp"
using namespace std;

/**
 * 
 * Constructor
 * @param nuber : the number we want to factorise
 * Initialise's the number an allocates the result we 1 single cell (the result we be reallocated each time we want to add a new factor)
*/
Factoriser::Factoriser(unsigned long long int number)
{
    this->number = number;
    this->factorisationResult = (unsigned long long int *)malloc(sizeof(unsigned long long int) * 1); // Allocate's memory for the first result
    this->countResults = 0;
}

/**
 * Uses Eratosthène's algorithm to factorise a given number
 * @param nbre  : the number we want to facorise
 * */
void Factoriser::factorisationNaive(unsigned long long int nbre)
{
    bool *tabPremiers = (bool *)malloc(sizeof(bool) * nbre);
    for (unsigned long long int i = 0; i < nbre; i++)
    {
        tabPremiers[i] = true;
    }
    tabPremiers[0] = false;
    tabPremiers[1] = false;

    bool dejaPremier = true;
    for (unsigned long long int i = 2; i <= sqrt(nbre); i++)
    {
        if (tabPremiers[i] == true)
        {

            unsigned long long int j = i + i;
            while (j < nbre)
            {
                tabPremiers[j] = false;

                j = j + i;     // tous les multiples de i sont barrés
                if (j == nbre) // nbre barré donc pas premier
                {
                    dejaPremier = false;
                    i = nbre; // end main loop
                    break;
                }
            }
        }
    }

    if (dejaPremier)
    {
        std::cout << nbre << " est déja un nombre premier" << endl;
        dejaPremier = true;
    }
    else
    {
        unsigned long long int positionplusPetitPremier = 2;
        unsigned long long int current = nbre;
        bool endFactorisation = false;

        do
        {
            while (current % positionplusPetitPremier == 0)
            {
                this->addNewFactorToResult(positionplusPetitPremier);

                // << positionplusPetitPremier << " divise " << current << endl;
                current = current / positionplusPetitPremier;
            }

            //trouver le prochain nombre premier
            do
            {
                positionplusPetitPremier += 1;
                if (positionplusPetitPremier > current)
                    endFactorisation = true;
            } while (tabPremiers[positionplusPetitPremier] == false);

        } while (endFactorisation == false);
    }
}

/**
 * Square and multiply algorithm using the binary representation of the number as the exponent
 * @param m : the base (that is m ^d mod n)
 * @param n : the modulus
 * @param d : the exponent
 * @return  : m ^d mod n
 */
unsigned int Factoriser::squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d)
{
    unsigned long long int a = 1;
    unsigned long long int b = m;

    unsigned long long int binarySize = floor(log2(n - 1)) + 1; // the size of the binary from a decimal number is: floor(log2(number)) + 1, note that we sended n-1 to <<decimalToBinary()>>
    for (unsigned long long int i = binarySize - 1; i >= 0; i--)
    {
        if (d[i] == 1)
        {
            a = (a * b) % n;
        }
        a = (a * a) % n;
        if (i == 0)
            break; // explicit break to prevent j (unsigned) to have a negative value => infinite loop
    }
    return a;
}

/**
 * Computes fermat's Factorisation
 * @param n  : the number we want to factorize 
 */
void Factoriser::fermatFactorisation(unsigned long long int n)
{
    if(n > 1000){
    unsigned long long int a = ceil(sqrt(n));
    unsigned long long int b2 = (a * a) - n;

    while (!isSquare(b2))
    {
        //a += 1;  // If first method a² - n
        b2 = b2 + (2 * a) + 1; //Second method a² - n
        //std::cout << "\na is " << a << endl;
        //std::cout << "\nb2 is " << b2 << endl;
        a += 1; // Remove line if first method is used
    }
    unsigned long long int res1 = a - sqrt(b2);
    unsigned long long int res2 = a + sqrt(b2);
    
    if (res1 > 3)
    {
        if (this->squareAndMultiply(2, res1, this->DecimalToBinary(res1 - 1)) != 1) // le premier facteur peut encore être décomposé
        {
            //cout << res1 << " encore" << endl;
            this->fermatFactorisation(res1);
        }
        else
        {
            this->addNewFactorToResult(res1);
        }
        
    }else
    {
        this->addNewFactorToResult(res1);
    }
    
    if (res2 > 3)
    {
        if (this->squareAndMultiply(2, res2, this->DecimalToBinary(res2 - 1)) != 1) // le deuxieme facteur peut encore être décomposé
        {

            //cout << res2 << " encore" << endl;
            this->fermatFactorisation(res2);
        }else
        {
            this->addNewFactorToResult(res2);
        }
        
    }else
    {
        this->addNewFactorToResult(res2);
    }
    }else
    {
        cout<<"NOTICE: send N = "<< n <<" to a native algorithm"<<endl;
        this->factorisationNaive(n);
    }
    
    
}

/**
 * Convert's a decimal number to it's binary representation
 * @param n : the decimal number
 * @return  :   an array of bits representing the binary representation of n
 */
short int *Factoriser::DecimalToBinary(unsigned long long int n)
{
    unsigned long long int binarySize = floor(log2(n)) + 1; // the size of the binary from a decimal number is: floor(log2(number)) + 1
    short int *a = (short int *)malloc(sizeof(short int) * binarySize);
    /*for (unsigned long long int i = 0; i < binarySize; i++)
    {
        a[i] = 0;
    }*/
    unsigned long long int i;
    for (i = 0; n > 0; i++)
    {
        a[i] = n % 2;
        n = n / 2;
    }
    /*
    std::cout << "Binary of the given number= ";
    for (unsigned long long int j = i - 1; j >= 0; j--)
    {
        std::cout << a[j];
        if (j == 0)
            break; // explicit break to prevent j (unsigned) to have a negative value => infinite loop
    }
    std::cout << "\n"
              << endl;*/

    return a;
}
void Factoriser::addNewFactorToResult(unsigned long long int result)
{

    this->factorisationResult[this->getCountResults()] = result;
    this->setCountResults(this->getCountResults() + 1);
    //Create a new int cell for a further next result
    this->factorisationResult = (unsigned long long int *)realloc(this->factorisationResult, sizeof(unsigned long long int) * this->getCountResults() +1);
}
void Factoriser::printFactorsResult()
{
    std::cout << "***** R E S U L T  A T ******" << endl;
    cout << "[" << this->getNumber() << "] = ";
    for (int i = 0; i < this->getCountResults(); i++)
    {
        cout << this->factorisationResult[i] << " * ";
    }
    cout << "1\n";
}
/**
 * Test is a number is a perfect square number
 * @param n : the number to be tested
 * @return true if the number is a perfect square and false if not
 */
bool Factoriser::isSquare(unsigned long long int n)
{
    unsigned long long int squareRoot = sqrt(n);
    if (squareRoot * squareRoot == n)
        return true;
    else
        return false;
}

//Getters and setters
void Factoriser::setNumber(unsigned long long int number)
{
    this->number = number;
}
unsigned long long int Factoriser::getNumber()
{
    return this->number;
}
int Factoriser::getCountResults()
{
    return this->countResults;
}
void Factoriser::setCountResults(int countResults)
{
    this->countResults = countResults;
}