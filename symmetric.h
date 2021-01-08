#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include<QString>

QString encrypt_affine(int a, int b, const QString &plaintext);
QString decrypt_affine(int a, int b, const QString &encryptedText);
int encrypt_affine_num(int a, int b, int n, int input);
int decrypt_affine_num(int a, int b, int n, int input);

QString encryptHill(const QString &text, int array[2][2]);
QString decryptHill(const QString &text, int array[2][2]);

QString encrypt_shift(int K, const QString text);
QString decrypt_shift(int K, const QString text);


QString encryptVigenere(const QString &keyword, const QString &input);
QString decryptVigenere(const QString &keyword, const QString &input);






#endif // SYMMETRIC_H
