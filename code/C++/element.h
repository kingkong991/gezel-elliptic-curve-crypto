#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <gmp.h>

/*
 *	Element of field GF((2^m)^4)
 *	Modulus:	x^159 + x^17 + 1 (wordlength 159)
 *			x^163 + x^7 + x^6 + x^3 + 1 (wordlength 163)
 */

class Element {
public:
	Element() { mpz_init(this->a); };
	Element(mpz_t& a) { mpz_init_set(this->a, a); };
	
	virtual ~Element();
	
	mpz_t getMP() { return this->a; };
	
	static void add(Element& T, Element& A, Element& B) { mpz_xor(T.getMP(), A.getMP(), B.getMP()); };
	static void multiply(Element& T, Element& Element& B);

private:
	mpz_t a;
}

#endif