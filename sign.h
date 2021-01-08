#ifndef SIGN_H
#define SIGN_H

#include<QVector>

QVector<int> signGamal(int p, int alpha, int a, int beta, int k, int x);
bool verifyGamal(int x, int s, int d, int alpha, int p, int beta);
QVector<int> signRSA(int n, int b, int x, int a, int n_public);
bool verifyRSA(int n, int b, int x, int y, int a, int n_public);



#endif // SIGN_H
