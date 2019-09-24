#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
using namespace std;

#include "Polynomial.h" // Class to represent polynomials
#include "Polynomial.cpp"

void makeList(int size, vector<double> &coeff_p) {
	int pos = 0;

	double value = 0;

	vector <double> coeff;
	
	for (int i = 0; i < size - 1; i++) { 
		cin >> pos;
		cin >> value;

		cin.ignore(250, ';'); //ignore stuff until you find a semi colon

		coeff.push_back(value);
	} 

	cin >> pos;
	cin >> value;
	coeff.push_back(value);

	//reverse the coefficients
	for (int j = size-1; j >= 0; j--) {
		coeff_p.push_back(coeff.at(j));
	}
}

int main () {
	string input; //make string to hold chars from test file

	int x = 0; //initialize length
	double y = 0; //initialize variable for evaluating polynomial
	double expValue = 0; //initialize expected value

	vector <double> coeff_p; //initialize vector for coeff_p1
	vector <double> coeff_p2; //initialize vector for coeff_p2;
	vector <double> coeff_get; //vector polynomial for get command
	vector <double> coeff_mult;
	vector <double> coeff_add;

	int pos = 0;

	while (cin >> input) { //read through all of the text file
	    if (input == "init") { // find init command and degree
		   	cin >> x;
		   	cout << "success" << endl;
	   }

	    else if (input == "coeff_p1") { //go to coefficient
	    	coeff_p.clear();
	    	makeList(x, coeff_p);
	    	cout << "success" << endl;
	    }

	    else if (input == "get") { //comparing default polynomial and expected
	    	Polynomial pA(x, coeff_p);

		    coeff_get.clear();
		    makeList(x, coeff_get);

		    Polynomial get(x, coeff_get);

		    if (pA.compare(get) == true) { //compare function shows both polynomials are equal
		    	cout << "success" << endl;
		    }

		    else {
		    	cout << "failure" << endl;
		    }
	  	}

	  	else if (input == "eval") {
		    Polynomial pA(x, coeff_p);

		    cin >> y;
		    cin >> expValue;

		    if (pA.eval(y, expValue) == true) {
		    	cout << "success" << endl;
		    }

		    else {
		    	cout << "failure" << endl;
		   	}
		}

	 	else if (input == "coeff_p2") {
		   	cout << "success" << endl;
		   	coeff_p2.clear();
		   	makeList(x, coeff_p2);
		}

		else if (input == "add") {
		 	Polynomial pA(coeff_p.size(), coeff_p);
		 	Polynomial pB(coeff_p2.size(), coeff_p2);

		 	coeff_add.clear();

		   	makeList(max(coeff_p.size(), coeff_p2.size()), coeff_add); //create add vector assuming highest degree

	    	Polynomial add1(coeff_add.size(), coeff_add);

	    	Polynomial sum = pA.sum(pB);

	    	if (sum.compare(add1) == true) {
	    		cout << "success" << endl;
	    	}

			else {
			    cout << "failure" << endl;
			}
		}

		else if (input == "mult") {
		   	Polynomial pB(coeff_p2.size(), coeff_p2);
		   	Polynomial pA(coeff_p.size(), coeff_p);

		   	coeff_mult.clear();
		   	makeList((coeff_p2.size() + coeff_p.size() - 1), coeff_mult);

		   	Polynomial mult1(coeff_mult.size(), coeff_mult);

	      	if (pA.mult(pB, mult1) == true) {
	      		cout << "success" << endl;
	      	}

			else {
			    cout << "failure" << endl;
			}
		}
	} 
  
    return 0; 
}