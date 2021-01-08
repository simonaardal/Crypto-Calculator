#ifndef SQUAREANDMULTIPLY_H
#define SQUAREANDMULTIPLY_H


#include<QVector>

using namespace std;

void toBinary(QVector<int> &vec, int number);
int squareAndMultiply(int n, int c, int a);
int squareAndMultiply(int &n, int &c, int &a, QString &text);
long int squareAndMultiply(long int n, long int c, long int a);
int mod(int a, int b);
long int mod(long int a, long int b);
int binaryToDecimal(QVector<int> binary);
void decimalToBinary(QVector<int> &vec, int number);
void fill(QVector<int> &vec);
int findInverse(int a, int n);
QVector<QVector<int>> findInverseMatrix(int array[2][2], int n);
bool isPrime(int n);

#endif // SQUAREANDMULTIPLY_H
