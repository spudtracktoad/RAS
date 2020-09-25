#include "rsaCrypto.h"

rsaCrypto::rsaCrypto(lint primeOne, lint primeTwo)
{
    this->p = primeOne;
    this->q = primeTwo;
    this->n = p*q;
    this->phi = (p-1)*(q-1);
    this->e = 5;
    this->FindE();
    this->d = this->extGCD(this->e, 1, this->phi);
}

rsaCrypto::rsaCrypto()
{
    this->n = p*q;
    this->phi = (p-1)*(q-1);
    this->FindE();
    this->FindD();
    /**cout << "p = " << this->p << endl;
    cout << "q = " << this->q << endl;
    cout << "n = " << this->n << endl;
    cout << "phi = " << this->phi << endl;
    cout << "e = " << this->e << endl;
    cout << "d = " << this->d << endl;**/
}

rsaCrypto::~rsaCrypto()
{
    //dtor
}

void rsaCrypto::encrypt(string inputFileName)
{
    int input;
    lint enInput;
    inFile.open(inputFileName);
    outFile.open("encrypted.txt");
    //cout << "encrypt" << endl;
    if(outFile.is_open())
    {
        if(inFile.is_open())
        {
            //cout << "File is open" << endl;
            do
            {
                //inFile.read(inBuffer, sizeof(int));
                inFile >> input;
                //cout << input << endl;
                enInput = this->encrypt(input);
                //cout << enInput << endl;
                outFile << enInput << endl;
            }while(!inFile.eof());
        }
        else
        {
            cout << "file not open" << endl;
        }
    }
    else
    {
        cout << "output file not open" << endl;
    }
    inFile.close();
    outFile.close();
}

void rsaCrypto::decrypt(string inputFileName)
{
    int deInput;
    lint input;
    this->encrypt(inputFileName);
    inFile.open("encrypted.txt");
    outFile.open("decrypted.txt");
    //cout << "decrypt " << endl;
    if(outFile.is_open())
    {
        if(inFile.is_open())
        {
            //cout << "File is open" << endl;
            do
            {
                //inFile.read(inBuffer, sizeof(int));
                inFile >> input;
                //cout << input << endl;
                deInput = this->decrypt(input);
                //cout << deInput << endl;
                if(!inFile.eof())
                   outFile << deInput << endl;
            }while(!inFile.eof());
        }
        else
        {
            cout << "file not open" << endl;
        }
    }
    else
    {
        cout << "output file not open" << endl;
    }
    inFile.close();
    outFile.close();
}

lint rsaCrypto::encrypt(int i)
{
    return modExponent(i, this->e, this->n);
}

lint rsaCrypto::decrypt(lint i)
{
    return modExponent(i, this->d, this->n);
}

lint rsaCrypto::modExponent(lint base, lint exponent, lint mod)
{
    lint result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

lint rsaCrypto::gcd(lint a, lint b)
{
    if (b == 0)
    {
        return a;
    }
   else
   {
       return gcd(b, a % b);
   }
   return -1;
}

void rsaCrypto::FindE()
{
    this->e = 2;
    while(this->e < this->phi)
    {
       if(gcd(this->e, this->phi)==1)
          break;
       else
          this->e++;
    }
}

void rsaCrypto::FindD()
{
    lint tmpD = 1;
    while(tmpD % this->e > 0)
        tmpD += this->phi;
    this->d = tmpD / this->e;
}

lint rsaCrypto::extGCD(lint a, lint b, lint n)
{
    lint* result;
    lint x0 = -1;
    result = extEuclid(a, n);
    //cout << result[0] << " " << result[1] << " " << result[2] << endl;
    if(b%result[0] == 0)
    {
        x0 = ((result[1] * (b / result[0]) % n ) + n) % n;
    }
    return x0;
}

lint* rsaCrypto::extEuclid(lint a, lint b)
{
    static lint result[3];
    lint *internal;
    lint tmp[3];
    if(b == 0)
    {
        result[0] = a;
        result[1] = 1;
        result[2] = 0;
    //cout << a << " " << b << " " << 0 << " " << result[0] << " " << result[1] << " " << result[2] << endl;
        return result;
    }
    else
    {
        internal = extEuclid(b, a%b);
        tmp[0] = internal[0];
        tmp[1] = internal[2];
        tmp[2] = internal[1] - a/b * internal[2];
    //cout << a << " " << b << " " << a/b << " " << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
    }

    result[0] = tmp[0];
    result[1] = tmp[1];
    result[2] = tmp[2];

    return result;
}
