#ifndef EXTENSION_H_
#define EXTENSION_H_

#include "element.h"

#include <gmp.h>

/*
 *	Extension field element in GF(n^4)
 *	Modulos are: x� + x + 1 and y� + (x+1)*y + 1
 *	
 *	Representation: (a + b*x) + (c + d*x)*y
 */

class Extension {
public:
	Extension() { this->a = Element(); this->b = Element(); this->c = Element(); this->d = Element(); };
	Extension(Element& a, Element& b, Element& c, Element& d) { this->a.set(a); this->b.set(b); this->c.set(c); this->d.set(d); };
	Extension(unsigned long a, unsigned long b, unsigned long c, unsigned long d) { this->a = Element(a); this->b = Element(b); this->c = Element(c); this->d = Element(d); };
	
	~Extension() { };
	
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
	
	void print() { gmp_printf("\n\tA = 0x%Zx\n\tB = 0x%Zx\n\tC = 0x%Zx\n\tD = 0x%Zx\n", this->a.getMP(), this->b.getMP(), this->c.getMP(), this->d.getMP()); };

	void printL() { gmp_printf("A = 0x%Zx - B = 0x%Zx - C = 0x%Zx - D = 0x%Zx\n", this->a.getMP(), this->b.getMP(), this->c.getMP(), this->d.getMP()); };

private:
	Element a, b, c, d;
};

#endif
