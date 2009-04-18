#include <gmp.h>

#include "extension.h"

void Extension::multiply(Extension& extA, Extension& extB) {	
	// Calculate m's
	Element m0, m1, m2, m3;
	
	m0.multiply(extA.getA(), extB.getA());
	m1.multiply(extA.getB(), extB.getB());
	m2.multiply(extA.getC(), extB.getC());
	m3.multiply(extA.getD(), extB.getD());
	
	// Calculate some temporary variables
	Element k0, k1, k2, k3, k4, k5, k6, k7;
	
	k0.add(extA.getA(), extA.getB());
	k1.add(extA.getC(), extA.getD());
	
	k2.add(extB.getA(), extB.getB());
	k3.add(extB.getC(), extB.getD());
	
	k4.add(extA.getB(), extA.getD());
	k5.add(extB.getB(), extB.getD());
	
	k6.add(extA.getA(), extA.getC());
	k7.add(extB.getA(), extB.getC());
	
	Element l0, l1, l2, l3;
	
	l0.multiply(k0, k2);
	l1.multiply(k1, k3);
	l2.multiply(k4, k5);
	l3.multiply(k6, k7);
	
	Element n0, n1, p0;
	
	n0.add(k0, k1);
	n1.add(k2, k3);
	
	p0.multiply(n0, n1);
	
	Element q0, q1, q3;
	
	q0.add(l1, m0);
	q1.add(q0, l0);
	q3.add(m2, m3);
	
	// [Calculate results]	
	// Calculate r0	
	this->a.add(q3, m0);
	this->a.add(this->a, m1);
	
	// Calculate r1
	this->b.add(q1, m2);
	
	// Calculate r2
	this->c.add(q0, q3);
	this->c.add(this->c, l2);
	this->c.add(this->c, l3);
	
	// Calculate r3
	this->d.add(q1, p0);
	this->d.add(this->d, m3);
	this->d.add(this->d, l3);
}

void Extension::square(Extension& ext) {
	this->a.add(ext.getA(), ext.getC());
	this->a.multiply(this->a, this->a);
	
	this->b.add(ext.getB(), ext.getD());
	this->b.multiply(this->b, this->b);
	
	this->a.add(this->a, this->b);
	
	this->c.multiply(ext.getC(), ext.getC());
	
	this->d.multiply(ext.getD(), ext.getD());
	this->d.add(this->d, this->c);

/*
	Element m0, m1, m2, m3;
	
	m0.square(ext.getA());
	m1.square(ext.getB());
	m2.square(ext.getC());
	m3.square(ext.getD());

	this->a.add(m0, m1);
	this->a.add(this->a, m2);
	this->a.add(this->a, m3);

	this->b.add(m1, m3);

	this->c.set(m2);

	this->d.add(m2, m3);
*/
}
