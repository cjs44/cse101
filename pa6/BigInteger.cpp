/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA6
 * BigInteger.cpp
 * BigInteger ADT
*************************************************/

#include <stdexcept>
#include <iostream>
#include <string>
#include "List.h"
#include "BigInteger.h"

// power and base
#define power 9
#define base 1000000000
//#define power 2
//#define base 100

// Class Constructors & Destructors ----------------------------------------
// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger(){
    // sign
    signum = 0;
    // magnitude
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    // set sign
    if (x < 0){
        signum = -1;
        // times -1 to make it positive
        x *= -1;
    }
    else if (x > 0){
        signum = 1;
    }
    else {
        signum = 0;
        digits.insertAfter(0);
    }
    // set digits
    while (x != 0){
        digits.insertAfter(x % base);
        x /= base;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	// precondition
    if (s.length() == 0 ){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    // set sign
    if (s[0] == '-' || s[0] == '+'){
        // check for only the sign
        if (s.length() > 1){
            if (s[0] == '-'){
                signum = -1;
            }
            else {
                signum = 1;
            }
            s.erase(0, 1);
        }
        // no digits
        else {
            throw std::invalid_argument("BigInteger: Constructor: no digits");
        }
    }
    // no + - means positive by default
    else {
        signum = 1;
    }
    // delete any leading 0s
	while (s[0] == '0'){
		s.erase(0,1);
	}
    // check for non-digit characters
    size_t nonDigit = s.find_first_not_of("0123456789");
    if (nonDigit != std::string::npos){
        throw std::invalid_argument("BigInteger: Constructor: non-digit character found");
    }
	// number to add to digits
	long num;
	while(s.length() >= power){
        // take chunk off end of s
		std::string chunk = s.substr(s.length() - power, power);
        // turn into number
		num = stol(chunk);
        // put into digits and delete off s
		digits.insertAfter(num);
		s.erase(s.length() - power, power);
	}
    // add any remaining to digits
	if (s.length() != 0){
		num = stol(s);
		digits.insertBefore(num);
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger &N){
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();
//---------------------------------------------------------------------------

// Access functions --------------------------------------------------------
// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger &N) const{
    // two lists to compare
    List A = digits;
    A.moveFront();
    List B = N.digits;
    B.moveFront();
    // two signs to compare
    int AS = signum;
    int BS = N.signum;
    // check easy cases
    // neg < pos
    if (AS == -1 && BS == 1){
        return -1;
    }
    // pos > neg
    else if (AS == 1 && BS == -1){
        return 1;
    }
    // longer neg < shorter neg
    else if (AS == -1 && A.length() > B.length()){
        return -1;
    }
    // longer pos > shorter pos
    else if (AS == 1 && A.length() > B.length()){
        return 1;
    }
    // compare values 
    while (A.position() < A.length() || B.position() < B.length()){
        // nums to compare
        long AN = A.peekNext();
        long BN = B.peekNext();
        // compare
        if (AN < BN){
            return -1;
        }
        else if (AN > BN){
            return 1;
        }
        A.moveNext();
        B.moveNext();
    }
    // they are equal return 0
    return 0;
}
//---------------------------------------------------------------------------

// Manipulation procedures -------------------------------------------------
// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate(){
        signum *= -1;
}
//---------------------------------------------------------------------------

// Helper Functions --------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    while (L.position() < L.length()){
        L.setAfter(L.peekNext() * -1);
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    // clear S 
    S.clear();
    // traverse A and B from back
    A.moveBack();
    B.moveBack();
    while (A.position() > 0 && B.position() > 0){
        // add each element
        long sum = A.peekPrev() + B.peekPrev() * sgn;
        A.movePrev();
        B.movePrev();
        // insert 
        S.insertAfter(sum);
    }
    // add any remaining elements
    while (A.position() > 0){
        // insert 
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }
    while (B.position() > 0){
        // insert 
        S.insertAfter(B.peekPrev() * sgn);
        B.movePrev();
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant 
// digits), then returns the sign of the resulting integer. Used 
// by add(), sub() and mult().
int normalizeList(List& L){
    long carry = 0;
    int sign = 1;
    // remove leading zeros
    L.moveFront();
    while (L.length() > 1 && L.front() == 0){
        L.eraseAfter();
    }
    // pull out a -1 if the first num is neg
    if (L.front() < 0){
        negateList(L);
        sign = -1;
    }
    // Traverse from back
    L.moveBack();
    while (L.position() > 0){
        long num = L.peekPrev();
        // carry from prev calculations
        if (carry != 0){
            num += carry;
            // back to 0
            carry = 0;
        }
        // num not in range 0 - (base - 1)
        if (num < 0){
            // num neg so increase it so it is in range
            carry = (num + 1) / base - 1;
            num -= carry * base;
        }
        else {
            // calculate carry to take off any extra
            carry = num / base;
            num %= base;
        }
        // change that num and move prev
        L.setBefore(num);
        L.movePrev();
    }
    // still something in carry
    if (carry != 0){
        L.insertBefore(carry);
        L.movePrev();
    }
    // Remove leading zeros again
    L.moveFront();
    while (L.length() > 1 && L.front() == 0) {
        L.eraseAfter();
    }
    // change sign to return
    if (L.front() < 0){
        sign *= -1;
    }
    else if (L.front() > 0){
        sign *= 1;
    }
    else if (L.length() == 1 && L.front() == 0){
        sign = 0;
    }
    return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    // prepend p zeros
    L.moveBack();
    for (int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    L.moveBack();
    while (L.position() > 0){
        long num = L.peekPrev() * m;
        L.setBefore(num);
        L.movePrev();
    }
}
//---------------------------------------------------------------------------

// BigInteger Arithmetic operations ----------------------------------------
// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger &N) const{
    // new BI
    BigInteger B;
    // this and N lists
    List TL = digits;
    List NL = N.digits;
    // apply BI signs to the lists
    if (signum == -1){
        negateList(TL);
    }
    if (N.signum == -1){
        negateList(NL);
    }
    // call sum list 
    sumList(B.digits, TL, NL, 1);
    // normalize
    B.signum = normalizeList(B.digits); 
    // sum = 0
    if (B.digits.length() == 0){
        B.signum = 0;
        B.digits.insertBefore(0);
        return B;
    }  
    return B;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger &N) const{
    // new BI
    BigInteger B;
    // this and N lists
    List TL = digits;
    List NL = N.digits;
    // apply BI signs to the lists
    if (signum == -1){
        negateList(TL);
    }
    if (N.signum == -1){
        negateList(NL);
    }
    // call sum list 
    sumList(B.digits, TL, NL, -1);
    // sub = 0
    if (B.digits.length() == 0){
        B.signum = 0;
        B.digits.insertBefore(0);
        return B;
    }
    // normalize
    B.signum = normalizeList(B.digits);    
    return B;
    return B;
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger &N) const{
    // new BI
    BigInteger B;
    // either BI 0, return empty
    if (signum == 0 || N.signum == 0){
        return B;
    }
    // this and N lists
    // for scalar mult
    //List TL = digits;
    List multiplicand = digits;
    List NL = N.digits;
    // num to multiply by
    long multiplier = 0;
    // count to shift by
    int count = 0;
    // loop of scalar mult, sum, normalize
    // traverse NL 
    NL.moveBack();
    while (NL.position() > 0){
        multiplier = NL.peekPrev();
        // multiply by num
        List temp = multiplicand;
        scalarMultList(temp, multiplier);
        // shift by count
        shiftList(temp, count);
        sumList(B.digits, B.digits, temp, 1);
        normalizeList(B.digits);
        count += 1;
        NL.movePrev();
    }
    // B sign is this sign * N sign
    B.signum = signum * N.signum;
    return B;
}
//---------------------------------------------------------------------------

// Other Functions ---------------------------------------------------------
// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s = "";
    // set sign
    if (signum == -1){
        s += '-';
    }
    if (signum == 0){
        s += '0';
        return s;
    }
    // traverse the list
    List D = digits;
    D.moveFront();
    // add the first chunk without zeros
    std::string firstChunk = std::to_string(D.peekNext());
    s += firstChunk;
    D.moveNext();
    // rest of it
    while (D.position() < D.length()){
        std::string chunk = std::to_string(D.peekNext());
        // add any zeros to front to make complete power chunk
        while (chunk.length() < power){
            chunk = '0' + chunk;
        }
        // add the chunk of digits
        s += chunk;
        D.moveNext();
    }
    return s;
}
//---------------------------------------------------------------------------

// Overriden Operators -----------------------------------------------------
// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B){
    if (A.compare(B) == 0){
        return true;
    }
    else {
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B){
    if (A.compare(B) == -1){
        return true;
    }
    else {
        return false;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B){
    if (A.compare(B) <= 0){
        return true;
    }
    else {
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B){
    if (A.compare(B) == 1){
        return true;
    }
    else {
        return false;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B){
    if (A.compare(B) >= 0){
        return true;
    }
    else {
        return false;
    }
}

// operator+()
// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B){
    BigInteger X = A;
    A = X.mult(B);
    return A;
}
//---------------------------------------------------------------------------