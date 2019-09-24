#include <iostream>
#include <stdlib.h>
using namespace std;

#ifndef 250POLYNOMIAL_H
#define 250POLYNOMIAL_H

//make a class for node
struct node {
    double data;
    node *next; //points to next thing
};

//make a class for linked list
struct linkedList {    
    node *head; //define the head and tail for node
    node *tail;
};

class Polynomial {
    // class variables
	private:
	int length;  // degree + 1
    linkedList poly_list;

    // class functions
    public:
    Polynomial (const int& length_p, vector <double> coeff_p); //constructor
    Polynomial(); //constructor to fill polynomial w/ 0s
    Polynomial(const Polynomial& p); //copy constructor
    ~Polynomial(); //destructor

    void print(); //print list

    //initialization and evaluation of a polynomial
    bool compare(const Polynomial& p); //compares current polynomial w/ expected
    bool eval( const float x, const float eValue) const;  //evaluate at x and compare w/ expected value

    // adding and multiplying polynomials
    bool add(const Polynomial& p, const Polynomial& ePoly) const;
    Polynomial sum(const Polynomial&p) const; //adds 2 polynomials w/o comparing them to expected value
	bool mult(const Polynomial& p, const Polynomial& ePoly) const;

};

#endif
