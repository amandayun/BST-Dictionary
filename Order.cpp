//amanda yun akyun@ucsc.edu 1903241 pa7

#include<iostream>
#include<string>
#include "Dictionary.h"
#include <fstream>
 

using namespace std;

int main(int argc, char *argv[]) {
	//read lines of input file
	//each line is a single string
	//insert strings as keys into the dictionary
	//value is the line number its on
	//writes two strings to output file
	//first is key: value\n pair
	//second is keys only
	
	if(argc<3){
		cerr << "Error: Input file name not specified" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	
	Dictionary A;
	
	string line;
	int counter = 1;
	while(getline(inputFile, line)){
		A.setValue(line, counter);
		counter++;
	}
	
	outputFile << A.to_string() << endl;
	outputFile << A.pre_string() << endl;

	
}