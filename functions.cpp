#include <iostream>
#include <cmath>
#include <chrono>
#include "functions.hpp"
using namespace std;
/**
 * Uses Eratosthène's algorithm to factorise a given number
 * @param nbre  : the number we want to facorise
 * */
void factorisationNaive(unsigned long long int nbre)
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
        unsigned long long int *tabFactorisation = (unsigned long long int *)malloc(sizeof(long long int));
        int tabFactorisationCurrentSize = 1; // Only one cell is allocated at begining
        int i = 0;                           // iterator to fill tabFactorisation
        unsigned long long int current = nbre;
        bool endFactorisation = false;

        do
        {
            while (current % positionplusPetitPremier == 0)
            {
                tabFactorisation[i] = positionplusPetitPremier;

                // << positionplusPetitPremier << " divise " << current << endl;
                current = current / positionplusPetitPremier;
                tabFactorisationCurrentSize += 1;
                tabFactorisation = (unsigned long long int *)realloc(tabFactorisation, tabFactorisationCurrentSize); // allocate 1 more cell for newt factor each time
                i++;
            }

            //trouver le prochain nombre premier
            do
            {
                positionplusPetitPremier += 1;
                if (positionplusPetitPremier > current)
                    endFactorisation = true;
            } while (tabPremiers[positionplusPetitPremier] == false);

        } while (endFactorisation == false);

        std::cout << "***** R E S U L T  A T ******" << endl;
        std::cout << "[" << nbre << "] = ";
        for (unsigned long long int j = 0; j < i; j++) //i is the size of tabFactorisation
        {
            std::cout << tabFactorisation[j] << " * ";
        }
        std::cout << " 1\n";
    }
}

/**
 * Square and multiply algorithm using the binary representation of the number as the exponent
 * @param m : the base (that is m ^d mod n)
 * @param n : the modulus
 * @param d : the exponent
 * @return  : m ^d mod n
 */
unsigned int squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d)
{
    unsigned long long int a = 1;
    unsigned long long int b = m;
    for (unsigned long long int i = 12; i >= 0; i--)
    {
        if (d[i] == 1)
        {
            a = (a * b) % n;
        }
        b = (b * b) % n;
        if (i == 0)
            break; // explicit break to prevent j (unsigned) to have a negative value => infinite loop
    }
    return a;
}

/**
 * Computes fermat's Factorisation
 * @param n  : the number we want to factorize 
 */
void fermatFactorisation(unsigned long long int n)
{
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
    std::cout << "***** R E S U L T  A T ******" << endl;
    std::cout << "[" << n << "] = ";
    std::cout << a - sqrt(b2) << " * " << a + sqrt(b2) << endl;
}

/**
 * Convert's a decimal number to it's binary representation
 * @param n : the decimal number
 * @return  :   an array of bits representing the binary representation of n
 */
short int *DecimalToBinary(unsigned long long int n)
{
    unsigned long long int binarySize = floor(log2(n)) + 1; // the size of the binary from a decimal number is: floor(log2(number)) + 1
    short int *a = (short int *)malloc(sizeof(short int) * binarySize);
    for (unsigned long long int i = 0; i < binarySize; i++)
    {
        a[i] = 0;
    }
    unsigned long long int i;
    for (i = 0; n > 0; i++)
    {
        a[i] = n % 2;
        n = n / 2;
    }
    std::cout << "Binary of the given number= ";
    for (unsigned long long int j = i - 1; j >= 0; j--)
    {
        std::cout << a[j];
        if (j == 0)
            break; // explicit break to prevent j (unsigned) to have a negative value => infinite loop
    }
    std::cout << "\n"
              << endl;
    return a;
}
/**
 * Test is a number is a perfect square number
 * @param n : the number to be tested
 * @return true is the number is a perfect square and false if not
 */
bool isSquare(unsigned long long int n)
{
    unsigned long long int squareRoot = sqrt(n);
    if (squareRoot * squareRoot == n)
        return true;
    else
        return false;
}