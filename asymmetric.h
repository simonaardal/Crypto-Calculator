#ifndef RSA_H
#define RSA_H

#include<QVector>


int encryptRSA(int n, int e, int x);
int decryptRSA(int n, int d, int y);
QVector<int> encryptGamal(int alpha, int k, int x, int beta, int p);
int decryptGamal(int y1, int y2, int p, int a);

#endif // RSA_H
