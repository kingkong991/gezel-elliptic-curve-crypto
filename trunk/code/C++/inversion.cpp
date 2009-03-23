/* 
 * Calculate the powering ladder for an exponentiation
 */

#include <stdio.h>

#include <string>
#include <vector>

#include <gmp.h>
 
int main () {
	mpz_t nr;
	mpz_init(nr);
	mpz_ui_pow_ui(nr, 2, 163);
	mpz_sub_ui(nr, nr, 2);
	
	gmp_printf("Nr = %Zd\n", nr);
	
	//mpz_init_set_str(nr, "11692013098647223345629478661730264157247460343806", 10);
	//mpz_init_set_str(nr, "30", 10);
	
	mpz_t q;
	mpz_init(q);
	
	// Start dividing as long as nr > 1
	std::vector<int> result;
		
	while (mpz_cmp_ui(nr, 1) > 0) {
		if (mpz_fdiv_q_ui(q, nr, 3) == 0) {
			mpz_set(nr, q);
			result.push_back(3);
		} else if (mpz_fdiv_q_ui(q, nr, 2) == 0) {
			mpz_set(nr, q);
			result.push_back(2);
		} else {
			mpz_sub_ui(nr, nr, 1);
			result.push_back(1);
		}
	}
	
	printf("[Compact]:\n");
	
	std::vector<int>::reverse_iterator rit = result.rbegin();
	int prev = *rit;
	
	unsigned int count = 0, switches = 0, mults = 0;
	
	for (; rit < result.rend(); rit++) {
		if (prev == *rit) {
			count++;
		} else {
			if (prev != 1)
				printf("%dx ^%d\n", count, prev);
			else
				printf("%dx *a\n", count);
				
			switches++;
			
			if (prev == 3)
				mults += count * 2;
			else
				mults += count;
				
			count = 1;
			prev = *rit;	
		}
	}
	
	if (prev != 1)
		printf("%dx ^%d\n", count, prev);
	else
		printf("%dx *a\n", count);
	
	if (prev == 3)
		mults += count * 2;
	else
		mults += count;
	
	printf("\n# of switches = %d\n# of multiplications = %d\n", switches, mults);
	
	/*printf("\n\n");
	
	rit = result.rbegin();
	for (; rit < result.rend(); rit++) {
		printf("%d ", *rit);
	}*/
		
	printf("\nDone");
}
