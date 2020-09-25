#include <iostream>
#include <fstream>
#include <cmath>
#include <stdint-gcc.h>

#define lint unsigned long long

using namespace std;

class rsaCrypto
{
    public:
        rsaCrypto(lint primeOne, lint primeTwo);
        rsaCrypto();
        virtual ~rsaCrypto();
        void encrypt(string inputFileName);
        void decrypt(string inputFileName);
        lint encrypt(int i);
        lint decrypt(lint i);

    protected:

    private:
        lint p = 59359;//1190494759;//53
        lint  q = 48611;//1400305337;//59
        lint  n;
        lint  e;
        lint  d;
        lint  phi;
        ofstream outFile;
        ifstream inFile;
        lint gcd(lint a, lint b);
        void FindE();
        void FindD();
        lint findD();
        lint extGCD(lint a, lint b, lint n);
        lint* extEuclid(lint a, lint b);
        lint modExponent(lint base, lint exponent, lint mod);

};