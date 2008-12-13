// Constants such as field size, ...

#ifndef CONSTANTS_INC
#define CONSTANTS_INC

#define const_m 4

// Reduction polynomial
// Test P = x^4 + x + 1 (= 19) (irreducible)
#define XOR_P(a,b) a[2:3] CONCATENATION ((ns(1)) a[1] ^ b) CONCATENATION ((ns(1)) a[0] ^ b)

// Curve parameters
//#define XOR_P(a, b) a[256:1222] CONCATENATION a[255] ^ b CONCATENATION a[1:254] CONCATENATION a[0] ^ b // Reduction polynomial P = x^1223 + x^255 + 1
#define curve_A 1
#define curve_B 0
#define curve_C 0		// c = b^(2^(m - 1)) (c^2 = b)

/* AND m-bit register (b) with 1-bit register (a): */
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>

// Redefine BOOST_PP_LIMIT_REPEAT to const_m
#define BOOST_PP_LIMIT_REPEAT const_m

/* z = next available repetition depth
	n = iteration number */
// From num - 1 to 0 (MSB first)
#define CONCATENATION #
#define EMPTY 
#define LPARENTHESE (
#define RPARENTHESE )
#define CONCAT_IF(cond) BOOST_PP_IF(cond, CONCATENATION, EMPTY)
#define AND1BIT(z, n, data) CONCAT_IF(BOOST_PP_NOT_EQUAL(0, n)) ((ns(1)) data[const_m - n - 1])
#define ANDMBITS(a, b) BOOST_PP_REPEAT(const_m, AND1BIT, a & b)

#endif /* CONSTANTS_INC */
