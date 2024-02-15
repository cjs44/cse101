/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA6
* Arithmetic.c 
* Arithmetic calls main() 
*************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]){
   // files and string
   ifstream in;
   ofstream out;
   string num1;
   string num2;
   string emptyLine;

   // check command line for correct number of arguments
   if (argc != 3){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if (!in.is_open()){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }
   out.open(argv[2]);
   if (!out.is_open()){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // line 1 has BI A
   getline(in, num1);
   BigInteger A = num1;
   // empty line
   getline(in, emptyLine);
   // line 3 has BI B
   getline(in, num2);
   BigInteger B = num2;

   /*f2.write(str(A)+'\n\n')
   f2.write(str(B)+'\n\n')
   f2.write(str(A+B)+'\n\n')
   f2.write(str(A-B)+'\n\n')
   f2.write(str(A-A)+'\n\n')
   f2.write(str(3*A-2*B)+'\n\n')
   f2.write(str(A*B)+'\n\n')
   f2.write(str(A**2)+'\n\n')
   f2.write(str(B**2)+'\n\n')
   f2.write(str(9*A**4+16*B**5)+'\n\n')*/

   // print
   out << A << endl << endl;
   out << B << endl << endl;

   // A + B
   BigInteger P1 = A + B;
   out << P1 << endl << endl;

   // A - B
   BigInteger P2 = A - B;
   out << P2 << endl << endl;

   // A - A
   BigInteger P3 = A - A;
   out << P3 << endl << endl;

   // 3*A - 2*B
   BigInteger M1 = A + A + A;
   BigInteger M2 = B + B;
   BigInteger P4 = M1 - M2;
   out << P4 << endl << endl;

   // A * B
   BigInteger P5 = A * B;
   out << P5 << endl << endl;

   // A ** 2
   BigInteger P6 = A * A;
   out << P6 << endl << endl;

   // B ** 2
   BigInteger P7 = B * B;
   out << P7 << endl << endl;

   // 9 * A**4 + 16 * B**5
   BigInteger E1 = A * A * A * A;
   // A1 = 9 * E1
   BigInteger A1 = E1;
   for (int i = 1; i < 9; i++){
      A1 += E1;
   }
   BigInteger E2 = B * B * B * B * B;
   // A2 = 16 * E2
   BigInteger A2 = E2;
   for (int i = 1; i < 16; i++){
      A2 += E2;
   }
   BigInteger P8 = A1 + A2;
   out << P8 << endl << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

