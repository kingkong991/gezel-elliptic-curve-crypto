#include <gmp.h>

#include "extension.h"

Extension::Extension() {
	Element zero;
	mpz_init(zero);
	
	Extension(zero, zero, zero, zero);
}

Extension::Extension(Element& a, Element& b, Element& c, Element& d) {
	this->a.set(a);
	this->b.set(b);
	this->c.set(c);
	this->d.set(d);
}

Extension::~Extension() { }
	
void Extension::multiply(Extension& ext) {
	
}