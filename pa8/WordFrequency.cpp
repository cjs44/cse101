/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA8
* WordFrequency.cpp
* Word Frequency calls main() 
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
    string line;
    size_t begin, end, length;
    string token;
    string tokenBuffer;
    Dictionary D;
    // delim
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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
    while (getline(in, line)){
        length = line.length();
        // for printing
        tokenBuffer = "";
        // split into word
        begin = min(line.find_first_not_of(delim, 0), length);
        end = min(line.find_first_of(delim, begin), length);
        token = line.substr(begin, end - begin);
        // loop until line is done
        while (token != ""){
            // all lower case
            for (string::size_type i = 0; i < token.length(); i++){
                token[i] = tolower(token[i]);
            }
            // already exists, increase the value
            if (D.contains(token)){
                D.getValue(token) += 1;
            }
            // new token with val 1
            else {
                D.setValue(token, 1);
            }
            // store for printing
            tokenBuffer += "   " + token + "\n";
            // next word
            begin = min(line.find_first_not_of(delim, end + 1), length);
            end = min(line.find_first_of(delim, begin), length);
            token = line.substr(begin, end - begin);
        }
    }

    // print 
    out << D << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}