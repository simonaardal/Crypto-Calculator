#ifndef MAC_H
#define MAC_H

#include<QVector>

QVector<int> findCaesarMAC(QVector<int> binaryInput, int n, int K, QVector<int> IV_binary);
QVector<int> findAffineMAC(QVector<int> binary, int A, int B, int n, QVector<int> IV_binary);


#endif // MAC_H
