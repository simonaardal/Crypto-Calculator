#include <iostream>
#include <math.h>
#include<bitset>
#include<vector>
#include<QVector>

using namespace std;

long int mod(long int a, int b){
    long int r = a % b;
    return r < 0 ? r + a : r;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int binaryToDecimal(QVector<int> binary){
    int index = binary.length();
    int sum = 0;
    for(int i = 0; i < binary.length(); i++){
        if(binary.at(i) == 1){
            sum += pow(2,index-1);
        }
        index--;
    }
    return sum;
}

void toBinary(QVector<int> &vec, int number){
    if (number > 1)
        toBinary(vec, number/2);
    vec.append(mod(number,2));

}

void fill(QVector<int> &vec){
    while(vec.length() % 4 != 0 || vec.length() == 0){
        vec.prepend(0);
    }

}




int squareAndMultiply(int n, int c, int a)
{
    QVector<int> vec;
    toBinary(vec, c);

    long int z = 1;
    for(int i : vec){
        z = mod((z*z),n);
        if(i == 1){
            z = mod((z * a),n);
        }
    }
    return z;
}



int squareAndMultiply(int &n, int &c, int &a, QString &text) {

    QVector<int> vec;
    toBinary(vec, c);
    int oldZ = 0;
    int z = 1;
    for(int i : vec){
        oldZ = z;
        z = mod((z*z),n);
        if(i == 1){
            z = mod((z * a),n);
            text += QString::number(i) + " :" + " z = " + QString::number(oldZ) + "²" + " * " + QString::number(a) + " = " + QString::number(z) + "\n";
        }else{
            text += QString::number(i) + " :" + " z = " + QString::number(oldZ) + "²" " = " + QString::number(z) + "\n";
        }
    }
    text += "\nz = " + QString::number(z);
    return z;
}

int findInverse(int a, int n){
    int a0 = n;
    int b0 = a;
    int t = 1;
    int t0 = 0;
    int q = floor(a0/b0);
    int r = a0 - (q*b0);
    while(r > 0){
        int temp = mod((t0 - (q*t)), n);
        t0 = t;
        t = temp;
        a0 = b0;
        b0 = r;
        q = floor(a0/b0);
        r = a0 - (q*b0);
    }
    if(b0 != 1){
        return -1;
    }else{
        return t;
    }
}

QVector<QVector<int>> findInverseMatrix(int array[2][2], int n){
    int temp = array[0][0] * array[1][1] - (array[0][1] * array[1][0]);

    int det = mod(temp, n);

    QVector<QVector<int>> vec = {{0,0},{0,0},{0,0}};

    if(det == 0){
        return vec;
    }

    int inverse = findInverse(det, n);

    int res[2][2] = {{inverse*array[1][1], -inverse*array[0][1]}, {-inverse*array[1][0], inverse*array[0][0]}};
    res[0][0] = mod(res[0][0], n);
    res[0][1] = mod(res[0][1], n);
    res[1][0] = mod(res[1][0], n);
    res[1][1] = mod(res[1][1], n);

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            vec[i][j] = res[i][j];
        }
    }
    vec[2][0] = det;
    vec[2][1] = inverse;

    return vec;

}

bool isPrime(int n){
    bool isPrime = true;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

