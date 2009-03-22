#include <gmp.h>

#include "Element.h"

void Element::multiply(Element& B) {
	mpz_t T;
	mpz_init(T);
	
	// Emulate hardware implementation.
	
	/*	Modulus:	x^159 + x^17 + 1 (wordlength 159)
	 *			x^163 + x^7 + x^6 + x^3 + 1 (wordlength 163)
	 */	 
	mpz_t mod;
	mpz_init_set(mod, "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000001", 2);
	
	// Length of modulus in base 2
	size_t mod_len = mpz_sizeinbase(mod, 2);
	
	for (unsigned long i = 0; i < (unsigned long) mod_len; i++) {
		if (mpz_tstbit(this->a, i) == 1) {
			mpz_xor(T, T, B);
		}
		
		if (m == 1) {
			mpz_xor(T, T, mod);
		}
		
		// Set m & T for next round
		m = mpz_tstbit(T, mod_len - 1);
		
		// Shift T by 1 bit to the left and clear MSB bit
		mpz_mul_2exp(T, T, 1);
		mpz_clrbit(T, mod_len);
	}
	
	mpz_set(this->a, T);
}