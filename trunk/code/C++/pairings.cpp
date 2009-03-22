#include <time.h>
#include <string>
#include <gmp.h>

#include "extension.h"

int main () {
	// Start measuring time
	clock_t start = clock();
	
	// Initialize P & Q values
	mpz_t P, Q;
	mpz_init(P);
	mpz_init(Q);
	
	mpz_set_str(P, "", 2);
	mpz_set_str(Q, "", 2);
	
	// Don't touch below this line
	
	// Set modulus
	mpz_t mod;
	mpz_init(mod);
	mpz_set_str(mod, "111010101", 2);

	// Length of modulus in base 2
	size_t mod_len = mpz_sizeinbase(mod, 2);
	
	

	// Return bit value at index
	// mpz_tstbit( mod, index)

	
	for (unsigned long i = 1; i <= max; i++) {
		mpz_ui_pow_ui(x, i, i);
		mpz_add(sum, sum, x);
	}
	
	gmp_printf("Sum = %Zu\n", sum);
	
	printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	exit(0);
}
