/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA8
* Order.cpp
* Order calls main() 
*************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
   // files and string
   ifstream in;
   ofstream out;
   string key;
   // line count
   int count = 1;
   Dictionary D;

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

   // add keys and vals
   while (getline(in, key)){
      D.setValue(key, count);
      count += 1;
   }

   // print 
   // key and value
   out << D << endl;
   // keys
   out << D.pre_string() << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

