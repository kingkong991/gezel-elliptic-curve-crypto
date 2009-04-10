// Constants such as field size, ...

#ifndef CONSTANTS_INC
#define CONSTANTS_INC

#define const_m 163
#define const_m_log 8

// Boost preprocessor libraries to allow for efficient XOR & AND implementations
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>

// Redefine BOOST_PP_LIMIT_REPEAT to const_m
#define BOOST_PP_LIMIT_REPEAT const_m

#define CONCATENATION #
#define EMPTY 
#define LPARENTHESE (
#define RPARENTHESE )

// Reduction polynomial:
// x^163 +  x^7  +  x^6  +  x^3  +   1
// (na)   (bit 7) (bit 6) (bit 3) (bit 0)
#define XOR_P(a, b) ((ns(155)) a[8:162]) CONCATENATION ((ns(1)) a[7] ^ b) CONCATENATION ((ns(1)) a[6] ^ b) CONCATENATION ((ns(2)) a[4:5]) CONCATENATION ((ns(1)) a[3] ^ b) CONCATENATION ((ns(2)) a[1:2]) CONCATENATION ((ns(1)) a[0] ^ b)

/* AND m-bit register (b) with 1-bit register (a): */
// See Boost manual for explanation
// From num - 1 to 0 (MSB first)
#define CONCAT_IF(cond) BOOST_PP_IF(cond, CONCATENATION, EMPTY)
#define AND1BIT(z, n, data) CONCAT_IF(BOOST_PP_NOT_EQUAL(0, n)) ((ns(1)) data[const_m - n - 1])
#define ANDMBITS(a, b) BOOST_PP_REPEAT(const_m, AND1BIT, a & b)

#endif /* CONSTANTS_INC */
