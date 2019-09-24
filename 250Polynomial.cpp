#include <iostream>
#include <vector>
#include <stdlib.h>
#include "250Polynomial.h" 
#include <math.h>
using namespace std;

//print linked list
void Polynomial::print () { //printing out linked list
	if (poly_list.head == NULL) { //nothing is in the linked list, so we're done
		return;
	}

	node *temp = poly_list.head; //assign temporary node as head	

	for (int i = 0; i < length; i++) { //go thru list w/o hitting end
		cout << temp->data << endl; //printing data from temp node
		temp = temp->next; //set temp node to next in list
	}
}

Polynomial::Polynomial(const int& length_p, vector <double> coeff_p) { //constructor
  length = length_p; //assign polynomial length

  poly_list.head = NULL;
  poly_list.tail = NULL;

    for (int i = 0; i < length; i++) {
		node *temp = new node; //make new node
		temp->data = coeff_p.at(i); //set coefficient as data in new node
		temp->next = NULL; //point to next 

		if (poly_list.head == NULL) { //there's nothing in the list so the node we made is the whole list
			poly_list.head = temp;
			poly_list.tail = temp;
		}

		else { //we add the node to the list
			poly_list.tail->next = temp; //make head point to temp
			poly_list.tail = temp;
		}
  	}

}

Polynomial::Polynomial() { //constructor to fill polynomial w/ 0s
	length = 0;
	poly_list.head = NULL;
	poly_list.tail = NULL;
}

Polynomial::Polynomial(const Polynomial& p) {
  length = p.length; //set degree to degree of incoming polynomial

  poly_list.head = NULL; 
  poly_list.tail = NULL;

  node *temp2 = p.poly_list.head; //make new node for traversing p linked list

    for (int i = 0; i < length; i++) { 
		node *temp = new node; //make new node for traversing default linked list

		temp->data = temp2->data; //set coefficient as data in new node
		temp->next = NULL; //point to next 

		if (poly_list.head == NULL) { //there's nothing in the list so the node we made is the whole list
			poly_list.head = temp;
			poly_list.tail = temp;
		}

		else { //we add the node to the list
			poly_list.tail->next = temp; //make head point to temp
			poly_list.tail = temp;
		}

		temp2 = temp2->next;
  	}
 
}

Polynomial::~Polynomial() { //destructor  
	node *current; //make node to be before current one

	if (poly_list.head == NULL) { //nothing is in the linked list, so we're done
		return;
	}

	while (poly_list.head !=NULL) { //go thru list w/o hitting end
		current = poly_list.head;
		poly_list.head = poly_list.head->next;
	}

	delete current;
}

bool Polynomial::compare (const Polynomial& p) {
	if (length < 0 || p.length < 0) { //if degree is negative 
    return false;
  }

  if (length != p.length) { //if the degrees of both polynomials are different, they can't be equal
    return false;
  }

  node *temp = poly_list.head; //assign temporary node as head of original polynomial
  node *temp2 = p.poly_list.head; //assign temporary node as head of 2nd polynomial	

  if (length == p.length) {
    for (int i = 0; i < length; i++) { //loop thru every coefficient til the term of the highest degree
      if (fabs(temp->data - temp2->data) > 0.00001) { //if the coefficients aren't the same, the 2 polynomials aren't equal
        return false;
      }
      temp = temp->next; //set temp node to next in list
      temp2 = temp2->next;
    }
  }
  
  return true; //if you reach this point, then the polynomials must have all the same coefficients and same degree
}

bool Polynomial::eval(const float x, const float eValue) const {
  if (length < 0) { //invalid degree
    // cout << "failure" << endl;
    return false;
  }

  float total = 0; //make spot for value
  node *temp = poly_list.head; //assign temporary node as head of polynomial

  int i = 0;
  
  for (int i = 0; i < length; i++) { //loop thru every coefficient til the term of the highest degree
    total = x * (total) + temp->data;
    temp = temp->next; //set temp node to next in list
  }

  if (total == eValue) { //evaluated polynomial is the same as expected value
  	// cout << "success" << endl;
  	return true;
  }

  else if (total != eValue) {
  	// cout << "failure" << endl;
  	return false;
  }

}

bool Polynomial::add(const Polynomial& p, const Polynomial& ePoly) const {
  if (length < 0 || p.length < 0) { //invalid polynomials
    return false;
  }

  int i = 0;
  double diff = 0;
  int P1Bigger = 1;

  vector <double> sum(length); //make vector to hold coefficients
  vector <double> psum(length); //make vector to hold coefficients

  if (length >= p.length) { //default polynomial is bigger
    // cout << "p1 is bigger" << endl;
    diff = length - p.length;
  }

  if (length < p.length) { //incoming polynomial is bigger
    // cout << "p2 is bigger" << endl;
    diff = p.length - length;
    P1Bigger = 0; //incoming polynomial is SMALLER (not bigger than default!!)
  }

  node *temp = poly_list.head; //node to traverse default polynomial
  node *ptemp = p.poly_list.head; //node to traverse second polynomial

  if (diff > 0) {
    for (int i = 0; i < diff; i++) {
      if (P1Bigger) {
      	// cout << "p1 is bigger and the difference is: " << diff << endl;
        sum.at(i) = temp->data;
        // cout << "value at start is:" << sum.at(i) << endl;
      }

      if (!P1Bigger) {
      	// cout << "p2 is bigger and the difference is" << diff << endl;
        psum.at(i) = ptemp->data;
        // cout << "value at start is: " << psum.at(i) << endl;
      }
      
    ptemp = ptemp->next; //move to next node in p polynomial
    temp = temp->next; //move to next node in default polynomial
    }
  }

  if (P1Bigger) {
  	// cout << "im adding things where p1 is bigger" << endl;

  	temp = poly_list.head; //redefine temp nodes in case they changed
  	ptemp = p.poly_list.head;

  	for (int i = 0; i < diff; i++) { //traverse linked list until you reach term where degree is the same
  		temp = temp->next;
  	}

  	for (int j = diff; j < length; j++) {
  		sum.at(j) = ptemp->data + temp->data;
  		// cout << "sum value is: " << sum.at(j) << endl;
  		ptemp = ptemp->next; //move onto next nodes
  		temp = temp->next;
  	}
  }

    if (!P1Bigger) {
  	// cout << "im adding things where p2 is bigger" << endl;

  	temp = poly_list.head; //redefine temp nodes in case they changed
  	ptemp = p.poly_list.head;

  	for (int i = 0; i < diff; i++) { //traverse linked list until you reach term where degree is the same
  		ptemp = ptemp->next;
  	}

  	for (int j = diff; j < p.length; j++) {
  		psum.at(j) = ptemp->data + temp->data;
  		// cout << "psum value is: " << psum.at(j) << endl;
  		ptemp = ptemp->next; //move onto next nodes
  		temp = temp->next;
  	}
  }

  //check if sum = expected polynomial
    if (length < p.length) {
    	Polynomial psumFinal(p.length, psum);
    	psumFinal.compare(ePoly); 
    	// cout << "the sum of the polynomials is" << endl;
    	// psumFinal.print();
    }

    if (length >= p.length) {
    	Polynomial sumFinal(length, sum);
    	sumFinal.compare(ePoly);
    	// cout << "the sum of the polynomials is" << endl;
    	// sumFinal.print();
    }

    return true;
	
}

bool Polynomial::mult(const Polynomial& p, const Polynomial& ePoly) const {
	if (length == 0) { //if the degree is 0, the second polynomial is a constant, so we have to add it to itself
    Polynomial product(p);

    for (int i = 1; i < poly_list.head->data; i++) {  
      product = product.sum(p); //call sum function (same as add function but no comparison at end)
    }

    product.compare(ePoly); //check if product = expected polynomial
  }

  if (p.length == 0) { 
    Polynomial product(*this);

    for (int i = 1; i < p.poly_list.head->data; i++) {
      product = product.sum(*this);
    }

    product.compare(ePoly);
  }

  int productDegree = p.length + length;
  vector <double> productCoeff(productDegree+1);

  for (int i = 0; i <= productDegree; i++) { // fill it with zeros
    productCoeff.at(i) = 0;
  }

  if (length > p.length) {
  	// cout << "p1 is bigger than p2" << endl;
  	node *temp = poly_list.head; //node to traverse default polynomial
  	node *ptemp = p.poly_list.head; //node to traverse second polynomial

    for (int i = 0; i <= length && temp != NULL; i++) {
      for (int j = 0; j <= p.length && ptemp != NULL; j++) {
        productCoeff.at(i+j) += (temp->data) * (ptemp->data);

        ptemp = ptemp->next;
      }

      temp = temp->next;
      ptemp = p.poly_list.head; //re initialize temp to front of list
    }
  } 

  else {
  	// cout << "p2 is bigger than or equal to p1" << endl;
  	node *temp = poly_list.head;
  	node *ptemp = p.poly_list.head;

    for (int i = 0; i <= p.length && ptemp != NULL; i++) {
      for (int j = 0; j <= length && temp != NULL; j++) {
        productCoeff.at(i+j) += (temp->data) * (ptemp->data);

        temp = temp->next;
      }

      ptemp = ptemp->next;
      temp = poly_list.head; //re initialize temp to front of list
    }
  }

  Polynomial product(productDegree-1, productCoeff);
  product.compare(ePoly);

  // cout << "the product of p1 and p2 is" << endl;
  // product.print();

}