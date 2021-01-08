#include "mac.h"
#include<QVector>
#include<math.h>
#include"calculations.h"
#include<iostream>
#include "symmetric.h"

QVector<int> findCaesarMAC(QVector<int> binary, int n, int K, QVector<int> IV_binary){

    QVector<int> temp;
    QVector<int> y_binary = IV_binary;
    int y = 0;
    int mult = 0;
    for(int i = 0; i < binary.length()+1; i++){
        if(i % 4 == 0 && i > 0){
            int temp1 = binaryToDecimal(temp);
            y = mod(temp1+K, n);
            y_binary.clear();
            toBinary(y_binary, y);
            fill(y_binary);
            temp.clear();
            mult++;

        }
        if(i != (binary.length())){
            temp.append(y_binary.at(i-(4*mult)) xor binary.at(i));
        }

    }
    return y_binary;
}

QVector<int> findAffineMAC(QVector<int> binary, int A, int B, int n, QVector<int> IV_binary){
    QVector<int> temp;
    QVector<int> y_binary = IV_binary;

    int y = 0;
    int mult = 0;
    for(int i = 0; i < binary.length()+1; i++){
        if(i % 4 == 0 && i > 0){
            int temp1 = binaryToDecimal(temp);

            y = encrypt_affine_num(A, B, n, temp1);

            y_binary.clear();
            toBinary(y_binary, y);
            fill(y_binary);
            temp.clear();
            mult++;

        }
        if(i != (binary.length())){
            temp.append(y_binary.at(i-(4*mult)) xor binary.at(i));
        }

    }
    return y_binary;
}
