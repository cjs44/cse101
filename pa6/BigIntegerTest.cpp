/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA6
 * BigIntegerTest.cpp
 * Tests for Big Integer ADT
 *************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(){

    // used base = 100 and power = 2 for initial testing
    
    // non digit
    //string str = "123d7";
    //BigInteger ND = BigInteger(str);

    // add
    long num = 111882133;
    string str1 = "111659179";
    BigInteger A = BigInteger(num);
    BigInteger B = BigInteger(str1);
    // print
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    // pos
    BigInteger T1 = A + B;
    cout << "A+B: " << T1 << endl;
    // neg
    string str2 = "-111882133";
    BigInteger C = BigInteger(str2);
    cout << "C: " << C << endl;
    BigInteger T2 = B + C;
    cout << "B+C: " << T2 << endl;
    // 0
    BigInteger T3 = A + C;
    cout << "A+C: " << T3 << endl;

    // sub
    string str3 = "132323481";
    string str4 = "522092567";
    BigInteger D = BigInteger(str3);
    BigInteger E = BigInteger(str4);
    BigInteger T4 = D - E;
    cout << "D-E: " << T4 << endl;

    // mult
    string str5 = "12348963";
    string str6 = "5612";
    BigInteger F = BigInteger(str5);
    BigInteger G = BigInteger(str6);
    cout << "F: " << F << endl;
    cout << "G: " << G << endl;
    BigInteger T5 = F * G;
    cout << "F*G: " << T5 << endl;

    string str7 = "11232324";
    string str8 = "2789738926742";
    BigInteger H = BigInteger(str7);
    BigInteger I = BigInteger(str8);
    cout << "H: " << H << endl;
    cout << "I: " << I << endl;
    BigInteger T6 = H * I;
    cout << "H*I: " << T6 << endl;

    string str9 = "-111122223333";
    string str10 = "111122223333";
    BigInteger J = BigInteger(str9);
    BigInteger K = BigInteger(str10);
    cout << "J: " << J << endl;
    cout << "K: " << K << endl;
    BigInteger T7 = J * K;
    cout << "J*K: " << T7 << endl;

    J *= K;
    cout << "J*K: " << J << endl;

    string t1 = "9063574346363325007361058";
    string t2 = "+4597814412658653960738664";
    BigInteger W = t1;
    BigInteger Q = t2;
    BigInteger P5 = W * Q;
    cout << P5 << endl;
    //41672632759912534648766230255815405104727028546512

    return 0;
}