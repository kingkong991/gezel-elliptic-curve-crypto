// Constants such as field size, ...

#ifndef CONSTANTS_INC
#define CONSTANTS_INC

#define const_m 5

// Reduction polynomial
#define const_P 0b10010

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
#define CONCAT_IF(cond) BOOST_PP_IF(cond, CONCATENATION, EMPTY)
#define AND1BIT(z, n, data) CONCAT_IF(BOOST_PP_NOT_EQUAL(0, n)) data[const_m - n - 1]
#define ANDMBITS(a, b) BOOST_PP_REPEAT(const_m, AND1BIT, (ns(1)) a & b)

#endif /* CONSTANTS_INC */
