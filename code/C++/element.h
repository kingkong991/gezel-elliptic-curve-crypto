#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <gmp.h>

/*
 *	Element of field GF(2^m)
 *	Modulus: x^163 + x^7 + x^6 + x^3 + 1 (wordlength 163)
 */

class Element {
public:
	Element() { mpz_init(this->a); };
	//Element(Element& A) { mpz_init_set(this->a, A.getMP()); };

	Element(mpz_t& a) { mpz_init_set(this->a, a); };
	Element(unsigned long a) { mpz_init_set_ui(this->a, a); };
	
	~Element() { };
	
	mpz_t& getMP() { return this->a; };

	void set(unsigned long a) { mpz_set_ui(this->a, a); };	
	void set(Element& A) { mpz_set(this->a, A.getMP()); };
	void set(mpz_t& a) { mpz_set(this->a, a); };
	
	void add(Element& A, Element& B) { mpz_xor(this->a, A.getMP(), B.getMP()); };
	void addOne() { if (mpz_tstbit(this->a, 0) == 0) { mpz_setbit(this->a, 0); } else { mpz_clrbit(this->a, 0); } };
	
	void multiply(Element& A, Element& B);
	void square(Element& A) { this->multiply(A, A); };
	
	void inverse(Element& A);
	
	bool isZero() { if (mpz_sgn(this->a) == 0) { return true; } return false; };
	
	void print() { gmp_printf("0x%Zx\n", this->a); };
	void printNNL() { gmp_printf("%Zx", this->a); };

private:
	mpz_t a;
};

#endif
