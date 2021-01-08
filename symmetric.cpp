#include "symmetric.h"
#include<calculations.h>


// *************************** AFFINE CIPHER *******************************************************************************************************************************

QString encrypt_affine(int a, int b, const QString &plaintext){
    QString upper = plaintext.toUpper();
    QString resString;
    for(auto &l : upper){
        ushort s = l.unicode();
        int encryptedValue = mod(((a*(s-65))+b),26);
        QChar d(encryptedValue+65);
        resString += d;
    }
    return resString;
}

QString decrypt_affine(int a, int b, const QString &plaintext){
    QString lower = plaintext.toLower();
    QString resString;
    for(auto &l : lower){
        ushort s = l.unicode();
        int encryptedValue = mod(((findInverse(a, 26) * ((s-97)-b))), 26);
        QChar d(encryptedValue+97);
        resString += d;
    }
    return resString;
}

int encrypt_affine_num(int a, int b, int n, int input){
    return mod(((a*input)+b),n);
}

int decrypt_affine_num(int a, int b, int n, int input){
    int inverse = findInverse(a, n);
    if(inverse == -1){
        return -1;
    }
    return mod((inverse * (input-b)),n);
}


// ******************* HILL CIPHER ***************************************************************************************************************************************


QString encryptHill(const QString &text, int array[2][2]){
    QVector<QChar> vec;
    for(auto &c : text){
        vec.append(c);
    }

    QVector<ushort> temp;
    QVector<ushort> hillRes;
    for(int i = 0; i < vec.length(); i++){
        if(i != 0 && i % 2 != 0){
            temp.append(vec.at(i).unicode()-65);

            hillRes.append(mod(((temp.at(0)*array[0][0]) + (temp.at(1)*array[1][0])),26));
            hillRes.append(mod(((temp.at(0)*array[0][1]) + (temp.at(1)*array[1][1])),26));

            temp.clear();
        }else{
            temp.append(vec.at(i).unicode()-65);
        }
    }

    QString resString;
    for(int i = 0; i < hillRes.length(); i++){
        resString += (hillRes[i]+65);
    }
    return resString;

}



QString decryptHill(const QString &text, int array[2][2])
{
    QVector<QChar> vec;
    for(auto &c : text){
        vec.append(c);
    }

    QVector<ushort> temp;
    QVector<ushort> hillRes;
    for(int i = 0; i < vec.length(); i++){
        if(i != 0 && i % 2 != 0){
            temp.append(vec.at(i).unicode()-65);

            hillRes.append(mod(((temp.at(0)*array[0][0]) + (temp.at(1)*array[1][0])),26));
            hillRes.append(mod(((temp.at(0)*array[0][1]) + (temp.at(1)*array[1][1])),26));

            temp.clear();
        }else{
            temp.append(vec.at(i).unicode()-65);
        }
    }

    QString resString;
    for(int i = 0; i < hillRes.length(); i++){
        resString += (hillRes[i]+65);
    }
    return resString;
}

// ************************* CAESAR CIPHER *******************************************************************************************************************************'

QString encrypt_shift(int K, const QString text){
    QString upper = text.toUpper();
    QString res;
    for(auto &l : upper){
        if(l != " "){
            ushort s = l.unicode();
            int temp = s - 65;
            int d = mod(temp+K, 26);
            QChar r(d+65);
            res += r;
        }
    }
    return res;
}

QString decrypt_shift(int K, const QString text){
    QString lower = text.toLower();
    QString res;
    for(auto &l : lower){
        if(l != " "){
            ushort s = l.unicode();
            int temp = s - 97;
            int d = mod(temp-K, 26);
            QChar r(d+97);
            res += r;
        }
    }
    return res;
}


// **************************** VIGENERE CIPHER ***********************************************************************************************************************


QString encryptVigenere(const QString &keyword, const QString &input){
    QString resString = "";
    int m = keyword.size();
    int counter = 0;
    for(auto &l : input){
        ushort valueA = l.unicode() - 97;
        ushort valueB = keyword.at(counter).unicode()-97;
        QChar b(mod(valueA+valueB, 26)+97);
        resString += b;
        counter++;
        if(counter == m){
            counter = 0;
        }
    }
    return resString;
}

QString decryptVigenere(const QString &keyword, const QString &input){
    QString resString = "";
    int m = keyword.size();
    int counter = 0;
    for(auto &l : input){
        ushort valueA = l.unicode() - 97;
        ushort valueB = keyword.at(counter).unicode()-97;
        QChar b(mod(valueA-valueB, 26)+97);
        resString += b;
        counter++;
        if(counter == m){
            counter = 0;
        }
    }
    return resString;
}


