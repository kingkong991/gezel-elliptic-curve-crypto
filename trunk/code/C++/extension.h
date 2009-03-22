#ifndef EXTENSION_H_
#define EXTENSION_H_

#include "element.h"

/*
 *	Extension field number in GF((2^m)^4)
 *	Modulos are: x² + 1 and y² + 1
 *	
 *	Representation: (a + bx) + (c + dx)y
 */

class Extension {
public:
	Extension();
	Extension(Element& a, Element& b, Element& c, Element& d);
	virtual ~Extension();
	
	Element getA() { return this->a; };
	Element getB() { return this->b; };
	Element getC() { return this->c; };
	Element getD() { return this->d; };
	
	void multiply(Extension& ext);

private:
	Element a, b, c, d;
}

#endif