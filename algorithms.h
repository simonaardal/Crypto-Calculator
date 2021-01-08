#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<QVector>

int gcd(int a, int b);
QVector<int> extended(int a, int b);

int pollard(int &n, int &B);
int pollard_findB(int &n);
int rho(int n, int x);
int pollardrho(int a, int n);
int pollardGCD(int a, int b);
int shank(int p, int alpha, int beta);


#endif // ALGORITHMS_H
