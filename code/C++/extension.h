#ifndef EXTENSION_H_
#define EXTENSION_H_

#include "element.h"

#include <gmp.h>

/*
 *	Extension field number in GF((2^m)^4)
 *	Modulos are: x² + x + 1 and y² + (x+1)*y + 1
 *	
 *	Representation: (a + b*x) + (c + d*x)*y
 */

class Extension {
public:
	Extension();
	Extension(Element& a, Element& b, Element& c, Element& d) { this->a.set(a); this->b.set(b); this->c.set(c); this->d.set(d); };
	
	virtual ~Extension();
	
	void setA(unsigned long a) { this->a.set(a); };
	void setB(unsigned long b) { this->b.set(b); };
	void setC(unsigned long c) { this->c.set(c); };
	void setD(unsigned long d) { this->d.set(d); };
	
	void setA(Element& A) { this->a.set(A); };
	void setB(Element& B) { this->b.set(B); };
	void setC(Element& C) { this->c.set(C); };
	void setD(Element& D) { this->d.set(D); };
	
	Element& getA() { return this->a; };
	Element& getB() { return this->b; };
	Element& getC() { return this->c; };
	Element& getD() { return this->d; };
	
	void multiply(Extension& extA, Extension& extB);
	void square(Extension& ext);
	
	void print() { gmp_printf("\n\tA = %Zu\n\tB = %Zu\n\tC = %Zu\n\tD = %Zu\n", this->a.getMP(), this->b.getMP(), this->c.getMP(), this->d.getMP()); };

private:
	Element a, b, c, d;
};

#endif
