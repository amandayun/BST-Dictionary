//amanda yun akyun@ucsc.edu 1903241 pa6

#include<iostream>
#include<string>
#include "Dictionary.h"
 

using namespace std;

int main(int argc, char *argv[]) {
	Dictionary A;
	
	A.setValue("c", 3);
	A.setValue("a", 1);
	A.setValue("b", 2);
	
	cout << "Dictionary A: " << A.to_string() <<endl;
	cout << "Dictionary A size: " << A.size() << endl;
	cout << "A contains a?: " << A.contains("a") << endl;
	cout << "Value of a: "<< A.getValue("a") << endl;
	
	cout << "has current?: " << A.hasCurrent() << endl;
	A.end();
	A.prev();
	cout << "has current now?: " << A.hasCurrent() << endl;
	cout << "current val: " << A.currentVal() << endl;
	cout << "current key: " << A.currentKey() << endl;
	
	A.begin();
	A.remove("a");
	
	A.setValue("e", 5);
	
	A.remove("c");
	
	cout << A.to_string() << endl;
	
	A.clear();
//	if (A.currentKey() != "g" || A.currentVal() != 30)
//		return 2;
//	A.remove("g");
//	if (A.hasCurrent())
//		return 3;
//
//	

	
	
	return 0;





	
}
