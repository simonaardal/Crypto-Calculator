#include "sign.h"
#include "calculations.h"
#include<iostream>

QVector<int> signGamal(int p, int alpha, int a, int beta, int k, int x)
{
    QVector<int> res;
    int y = squareAndMultiply(p, k, alpha);
    res.append(y);
    int k_inverse = findInverse(k, p-1);
    res.append(mod((x - (y*alpha))*k_inverse, p-1));
    return res;
}

bool verifyGamal(int x, int s, int d, int alpha, int p, int beta)
{
    int x1 = mod(squareAndMultiply(p, s, beta)*squareAndMultiply(p, d, s),p);
    return x1 == squareAndMultiply(p, x, alpha) ? true : false;

}

QVector<int> signRSA(int n, int b, int x, int a, int n_public)
{
    int y = squareAndMultiply(n, a, x);
    int encryptedX = squareAndMultiply(n_public, b, x);
    int encryptedY = squareAndMultiply(n_public, b, y);
    QVector<int> res;
    res.append(encryptedX);
    res.append(encryptedY);
    return res;
}

bool verifyRSA(int n, int b, int x, int y, int a, int n_public)
{
    int decryptedX = squareAndMultiply(n, a, x);
    int decryptedY = squareAndMultiply(n, a, y);
    if(squareAndMultiply(n_public, b, decryptedY) == decryptedX){
        return true;
    }else{
        return false;
    }
}
