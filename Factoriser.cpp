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
        this->addNewFactorToResult(nbre);
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
unsigned int Factoriser::squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d, short int nbreRepeat)
{
    if (n == 2 && m == 2) // Tester si 2 est premier avec cette methode de Rabin-Miller echouerait
        return 1;
    for (int i = 0; i < nbreRepeat; i++)
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
                break; // explicit break to prevent i (unsigned) to have a negative value => infinite loop
        }
        if (a != 1)
            return a;

        m += 1;
    }
    return 1;
}

/**
 * Computes fermat's Factorisation
 * @param n  : the number we want to factorize 
 */
void Factoriser::fermatFactorisation(unsigned long long int n)
{
    if (n > 100000)
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
        unsigned long long int res1 = a - sqrt(b2);
        unsigned long long int res2 = a + sqrt(b2);

        if (res1 > 3)
        {
            if (this->squareAndMultiply(2, res1, this->DecimalToBinary(res1 - 1), 3) != 1) // le premier facteur peut encore être décomposé
            {
                this->fermatFactorisation(res1);
            }
            else
            {
                this->addNewFactorToResult(res1);
            }
        }
        else
        {
            this->addNewFactorToResult(res1);
        }

        if (res2 > 3)
        {
            if (this->squareAndMultiply(2, res2, this->DecimalToBinary(res2 - 1), 3) != 1) // le deuxieme facteur peut encore être décomposé
            {
                this->fermatFactorisation(res2);
            }
            else
            {
                this->addNewFactorToResult(res2);
            }
        }
        else
        {
            this->addNewFactorToResult(res2);
        }
    }
    else
    {
        cout << "+++ NOTICE: send N = " << n << " to a native algorithm" << endl;
        this->factorisationNaive(n);
    }
}
void Factoriser::recurvivePollardMinusOne(unsigned long long int nbre, unsigned long long int borne, unsigned long long int a)
{
    bool continuer = true;
    do
    {
        //cout << "ok" << endl;
        if (this->squareAndMultiply(2, nbre, this->DecimalToBinary(nbre - 1), 3) != 1)
        {
            unsigned long long int newFactor = this->pollardMinusOne(nbre, borne, a);
            if (newFactor > 1)
            {
                if (this->squareAndMultiply(2, newFactor, this->DecimalToBinary(newFactor - 1), 3) != 1) // Le facteur trouvé n'est pas encore un nombre premier
                {
                    //cout <<newFactor<< " pas premier"<<endl;
                    this->recurvivePollardMinusOne(newFactor, borne, a);
                }
                else
                {
                    // cout << newFactor << " est un diviseur car +++++++" << endl;
                    this->addNewFactorToResult(newFactor);
                }

                nbre = nbre / newFactor;
            }
            else if (newFactor == 1)
            {
                if (this->pollardMinusOne(nbre, borne + 1, a) < 1)
                {
                    //si la borne +1 sera petite (sachant que celle actuelle est grande) alors
                    // l’ordre de (a) modulo N est plus petit que φ(N), dans ce cas redémarrer l’algorithme avec un (a) différent
                    //pourrait réussir la factorisation 
                    cout << "++++NOTICE Changement du parametre (a)--------------------" << endl;
                    a = a + 1;
                }
                borne = borne + 1;
                //cout << "Borne augmentée" << borne << " N = " << nbre << endl;
            }
            else
            {
                borne = borne - 1;
                //cout << "Borne reduite" << borne << " N = " << nbre << endl;
                if (borne == 0)
                {
                    //cout << "Borne reduite" << nbre << endl;
                    this->addNewFactorToResult(nbre);
                    continuer = false;
                }
            }
        }
        else
        {
            continuer = false;
            this->addNewFactorToResult(nbre);
            //cout << "aussi " << nbre << endl;
        }

    } while (continuer == true);
}
unsigned long long int Factoriser::pollardMinusOne(unsigned long long int nbre, unsigned long long int borne, unsigned long long int a)
{

    unsigned long long int e = factorielle(borne);
    //unsigned long long int a = 2; //needs to be random < nbre
    unsigned long long int x = this->pgcd(a, nbre);
    unsigned long long int errorCode = 0;
    if (x != 1)
    {
        //cout << x << " est un diviseur++++++++" << endl;
        return x;
    }
    unsigned long long int b = this->squareAndMultiply(a, nbre, this->DecimalToBinary(e), 3);
    x = this->pgcd(b - 1, nbre);
    if (x == nbre)
    {
        //cout << " echec borne trop grande" << endl;
        errorCode = 0; // Code d'erreurr de borne trop grande
    }
    else if (x == 1)
    {
        //cout << " echec borne trop petite" << endl;
        errorCode = 1; // Cde d'erreur de borne trop petite
    }
    else
    {
        //cout << x << " est un diviseur +++++++" << endl;
        return x;
    }

    return errorCode;
}
//Donald Knuth, dans The Art of Computer Programming écrit une version itérative de l'algorithme d'Euclide1 :
unsigned long long int Factoriser::pgcd(unsigned long long int a, unsigned long long int b)
{
    /*fonction euclide(a, b)
    tant que b ≠ 0
       t := b; 
       b := a modulo b; 
       a := t; 
    retourner a*/
    unsigned long long int t;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
unsigned long long int Factoriser::factorielle(unsigned long long int nbre)
{
    if (nbre == 1 || nbre == 0)
        return 1;
    else
    {
        return (nbre * this->factorielle(nbre - 1));
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
    this->factorisationResult = (unsigned long long int *)realloc(this->factorisationResult, sizeof(unsigned long long int) * this->getCountResults() + 1);
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