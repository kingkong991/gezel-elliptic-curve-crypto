#include <gmp.h>

#include "Element.h"

static void Element::multiply(Element& T, Element& A, Element& B) {
	// Emulate hardware implementation.
	
	mpz_set_ui(T, 0);
	
	// Modulus:	x^163 + x^7 + x^6 + x^3 + 1 (wordlength 163)
	mpz_t mod;
	mpz_init(mod);
	
	mpz_t sum;
	mpz_init(sum);
	
	mpz_set_ui(sum, 1);
	mpz_mul_2exp(mod, sum, 163);
	
	mpz_mul_2exp(sum, sum, 7);
	mpz_add(mod, mod, sum);
	mpz_set_ui(sum, 1);
	
	mpz_mul_2exp(sum, sum, 6);
	mpz_add(mod, mod, sum);
	mpz_set_ui(sum, 1);
	
	mpz_mul_2exp(sum, sum, 3);
	mpz_add(mod, mod, sum);
	mpz_set_ui(sum, 1);
	
	mpz_add(mod, mod, sum);
	
	gmp_printf("Mod = %Zx\n", mod);
	
	// Length of modulus in base 2
	size_t mod_len = mpz_sizeinbase(mod, 2);
	
	for (unsigned long i = 0; i < (unsigned long) mod_len; i++) {
		if (mpz_tstbit(A, i) == 1) {
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
	
	
}