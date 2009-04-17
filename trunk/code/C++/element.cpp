#include "element.h"

#include <gmp.h>

void Element::multiply(Element& A, Element& B) {
	// Emulate hardware implementation.
	
	// Set result to 0
	mpz_t result;
	mpz_init(result);
	
	// Modulus: x^163 + x^7 + x^6 + x^3 + 1 (wordlength 163)
	mpz_t mod;
	mpz_init(mod);
	mpz_set_str(mod, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011001001", 2);
	
	//gmp_printf("Mod = %Zx\n", mod);
	
	// Length of modulus in base 2
	int mod_len = 163;
	
	//printf("Len = %d\n", mod_len);
	
	int m = 0;
	for (long i = (long) mod_len; i > 0; i--) {
		if (mpz_tstbit(A.getMP(), i - 1) == 1) {
			mpz_xor(result, result, B.getMP());
		}
		
		if (m == 1) {
			mpz_xor(result, result, mod);
		}
		
		// Set m & T for next round
		m = mpz_tstbit(result, mod_len - 1);
		
		// Shift T by 1 bit to the left and clear MSB bit
		mpz_clrbit(result, mod_len - 1);
		mpz_mul_2exp(result, result, 1);
		
		/*printf("[Mult] i = %d - T = ", mod_len - i + 2);
		gmp_printf("0x%Zx\n", result);*/
	}
	
	// Shift result back 1 place & place m back in front
	mpz_tdiv_q_2exp(result, result, 1);
	if (m == 1) {
		mpz_setbit(result, 162);
	}
	
	/*printf("[Mult] i = 0 - T = ");
	gmp_printf("0x%Zx\n", result);*/
	
	// Set result
	mpz_set(this->a, result);
}

void Element::inverse(Element& A) {
	Element tempA = Element();
	Element tempB = Element();
	
	// Calculate a^3
	tempA.square(A);
	tempA.multiply(tempA, A);
	
	tempB.set(tempA);
	
	//printf("\n\ta^3 =           ");
	//tempA.print();
	
	// Calculate a^(2^4 - 1)
	tempA.square(tempA);
	tempA.square(tempA);
	
	//printf("\tb^4 =           ");
	//tempA.print();
	
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^4 - 1) =   ");
	//tempA.print();
	
	// Calculate a^(2^5 - 1)
	tempA.square(tempA);
	tempA.multiply(tempA, A);
	
	//printf("\ta^(2^5 - 1) =   ");
	//tempA.print();
	
	// Calculate a^(2^10 - 1)
	tempB.set(tempA);
	for (int i = 0; i < 5; i++) {
		tempA.square(tempA);
	}
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^10 - 1) =  ");
	//tempA.print();
	
	// Calculate a^(2^20 - 1)
	tempB.set(tempA);
	for (int i = 0; i < 10; i++) {
		tempA.square(tempA);
	}
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^20 - 1) =  ");
	//tempA.print();
	
	// Calculate a^(2^40 - 1)
	tempB.set(tempA);
	for (int i = 0; i < 20; i++) {
		tempA.square(tempA);
	}
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^40 - 1) =  ");
	//tempA.print();
	
	// Calculate a^(2^80 - 1)
	tempB.set(tempA);
	for (int i = 0; i < 40; i++) {
		tempA.square(tempA);
	}
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^80 - 1) =  ");
	//tempA.print();
	
	// Calculate a^(2^81 - 1)
	tempA.square(tempA);
	tempA.multiply(tempA, A);
	
	//printf("\ta^(2^81 - 1) =  ");
	//tempA.print();
	
	// Calculate a^(2^162 - 1)
	tempB.set(tempA);
	for (int i = 0; i < 81; i++) {
		tempA.square(tempA);
	}
	tempA.multiply(tempA, tempB);
	
	//printf("\ta^(2^162 - 1) = ");
	//tempA.print();
	
	// Calculate a^-1
	tempA.square(tempA);
	
	//printf("\ta^-1 =          ");
	//tempA.print();
	
	// Set result
	this->set(tempA);
}
