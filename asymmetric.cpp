#include<calculations.h>

#include "asymmetric.h"

int encryptRSA(int n, int x, int e){
    return squareAndMultiply(n, e, x);
}

int decryptRSA(int n, int y, int d){
    return squareAndMultiply(n, d, y);
}

QVector<int> encryptGamal(int alpha, int k, int x, int beta, int p)
{
    QVector<int> vec;
    vec.append(squareAndMultiply(p, k, alpha));
    int temp = squareAndMultiply(p, k, beta);
    vec.append(mod(temp*x, p));
    return vec;
}

int decryptGamal(int y1, int y2, int p, int a)
{

    return mod(y2*(findInverse(squareAndMultiply(p, a, y1), p)), p);
}
