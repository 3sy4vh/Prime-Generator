#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <fstream>
#include <string>
using Clock = std::chrono::steady_clock;
using namespace std;

const int primeCount = 200;
long long int* primes = new long long int[primeCount] { 0 };

int primesGenerated = 2;

bool checkPrime(__int64 number)
{
    for (int i = 0; i < primesGenerated; i++)
    {
        if (primes[i] * primes[i] > number)
        {
            return true;
        }

        if (number % primes[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    primes[0] = 2;
    primes[1] = 3;

    long long int n = 6;

    Clock::time_point startTime = Clock::now();
    Clock::time_point prevOutputTime = Clock::now();
    
    while (primesGenerated < primeCount)
    {
        
        if (checkPrime(n - 1))
        {
            primes[primesGenerated] = n - 1;
            primesGenerated++;
        }
        if (checkPrime(n + 1))
        {
            primes[primesGenerated] = n + 1;
            primesGenerated++;
        }

        n += 6;

        if ((chrono::duration_cast<chrono::seconds>(Clock::now() - prevOutputTime)).count() >= 5)
        {
            cout << "Primes Generated:  " << primesGenerated << endl;
            cout << "Largest prime:     " << primes[primesGenerated - 1] << endl;
            prevOutputTime = Clock::now();
        }
    }

    Clock::time_point endTime = Clock::now();

    for (int i = max(0, primeCount - 1000); i < primeCount; i++)
    {
        cout << i + 1 << "        " << primes[i] << endl;
    }

    float runTime = (chrono::duration_cast<chrono::seconds>(endTime - startTime)).count();

    cout << "Runtime:           " << runTime << endl;


    //Overwriting values with indexes
    if (true)
    {
        for (int i = 0; i < primeCount; i++)
        {
            primes[i] = i;
        }
    }

    //Output
    std::ofstream out("primes.bin", std::ios::binary);
    for (int i = 0; i < primeCount; i++)
    {
        out.write((const char*)&primes[i], sizeof (long long int));
    }
    cout << "Write time:        " << (chrono::duration_cast<chrono::seconds>(Clock::now() - endTime)).count() << " seconds" << endl;
}