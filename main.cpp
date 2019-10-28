#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
using namespace std;
unsigned long long int squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d);
void fermatFactorisation(unsigned long long int n);
void factorisationNaive(unsigned long long int nbre);
short int *DecimalToBinary(unsigned long long int n);
bool isSquare(unsigned long long int n);
int main(int argc, char *argv[])
{

    //DecimalToBinary(1844674407370955161);
    /*
    short d[] = {1, 0, 1, 1, 1, 0};
    if (squareAndMultiply(2, 47, d) == 1) // Rabin-Miller: 2^(47-1) mod 47
    {
        cout << "nombre premier";
    }

    fermatFactorisation(6);*/

    /*long double a = pow(2, 67 - 1) % 9;
    cout << (a) % 67 << endl;
    std::cout << "Entrer le nombre à factoriser" << endl;
    unsigned unsigned long long int nbre;
    cin >> nbre;
    
 
    clock_t begin = clock();

    // Get ending timepoint
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken by function: "
         << time_spent << " seconds" << endl;*/
    std::cout << "Entrer le nombre à factoriser:";
    unsigned long long int nbre;
    cin >> nbre;

    std::cout << "--------------------------" << endl;
    std::cout << "DEBUT FACTORISATION NAIVE" << endl;
    factorisationNaive(nbre);
    std::cout << "FIN FACTORISATION NAIVE" << endl;
    std::cout << "--------------------------" << endl;

    std::cout << endl;
    std::cout << "DEBUT FACTORISATION FERMAT" << endl;
    /*if (squareAndMultiply(2, nbre, DecimalToBinary(nbre - 1)) == 1)
    { // Rabin-Miller: 2^(47-1) mod 47
        std::cout << nbre << " est déja un nombre premier";
    }
    else
    {
        fermatFactorisation(nbre);
    }*/
    fermatFactorisation(nbre);
    std::cout << "FIN FACTORISATION FERMAT" << endl;
    std::cout << "--------------------------" << endl;
    return 0;
}

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

unsigned long long int squareAndMultiply(unsigned long long int m, unsigned long long int n, short int *d)
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

short int *DecimalToBinary(unsigned long long int n)
{
    unsigned long long int binarySize = floor(log2(n)) + 1;
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

bool isSquare(unsigned long long int n)
{
    unsigned long long int squareRoot = sqrt(n);
    if (squareRoot * squareRoot == n)
        return true;
    else
        return false;
}