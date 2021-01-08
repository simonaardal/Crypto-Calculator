
#include<QString>
#include<algorithms.h>
#include<math.h>
#include<calculations.h>
#include<vector>
#include<iostream>

int gcd(int a, int b)
{
    if (a == 0){
        return b;
    }
    return gcd(b % a, a);
}

QVector<int> extended(int a, int b){
    int a0 = a;
    int b0 = b;
    int t0 = 0;
    int t = 1;
    int s0 = 1;
    int s = 0;
    int q = floor(a0/b0);
    int r = a0 - (q*b0);

    while(r > 0){
        int temp = t0 - (q*t);
        t0 = t;
        t = temp;
        temp = s0 - (q*s);
        s0 = s;
        s = temp;
        a0 = b0;
        b0 = r;
        q = floor(a0/b0);
        r = a0 - (q*b0);
    }
    r = b0;

    QVector<int> vec;
    vec.append(r);
    vec.append(s);
    vec.append(t);
    return vec;
}


int pollard(int &n, int &B){
    int a = 2;
    for(int j = 2; j < (B+1); j++){
        a = squareAndMultiply(n, j, a);
    }
    int d = gcd(a-1, n);
    if(d > 1 && d < n){
        return d;
    }else{
        return -1;
    }
}

int pollard_findB(int &n){
    int d = -1;
    int teller = 0;
    while(d <= 1){
        teller++;
        d = pollard(n, teller);
    }
    return teller;
}

int f(int x, int n){
    return mod(x*x+1, n);
}

int rho(int n, int x){

    vector<int> vec;
    vec.emplace_back(x);

    int d = 0;
    int i = 2;
    bool run = true;
    while(run){
        x = f(x, n);
        //cout << x << endl;
        vec.emplace_back(x);
        if(i%2 == 0){
            d = gcd(x-vec.at((i-2)/2), n);
        }
        i++;
        if(d == n){
            run = false;
        }else if(d == 1){

        }else{
            return abs(d);
        }
    }
    return -1;
}

int shank(int p, int alpha, int beta){
    int m = ceil(sqrt(p-1));

    QVector<int> listA;
    int z = squareAndMultiply(p, m, alpha);
    for(int i = 0; i < m; i++){
        listA.append(squareAndMultiply(p, i, z));
    }
    QVector<int> listACopy;
    listACopy.resize(listA.size());
    copy(listA.begin(), listA.end(), listACopy.begin());

    sort(listA.begin(), listA.end());

    QVector<int> listB;
    int temp;
    for(int i = 0; i < m; i++){
        if(i == 0){
            temp = beta;
        }else{
            temp = mod((temp*findInverse(alpha, p)),p);
        }
        listB.append(temp);
    }
    QVector<int> listBCopy;
    listBCopy.resize(listB.size());
    copy(listB.begin(), listB.end(), listBCopy.begin());

    sort(listB.begin(), listB.end());

    int value;
    for(int i = 0; i < listA.size(); i++){
        for(int j = 0; j < listB.size(); j++){
            if(listA.at(i) == listB.at(j)){
                value = listA.at(i);
            }
        }
    }

    int indexA = 0;
    for(int i = 0; i < listACopy.size(); i++){
        if(listACopy.at(i) == value){
            indexA = i;
        }
    }

    int indexB = 0;
    for(int i = 0; i < listBCopy.size(); i++){
        if(listBCopy.at(i) == value){
            indexB = i;
        }
    }

    return mod(m*indexA + indexB, p-1);
}
