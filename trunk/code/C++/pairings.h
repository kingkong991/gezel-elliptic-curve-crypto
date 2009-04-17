#ifndef PAIRINGS_H_
#define PAIRINGS_H_

#include "element.h"
#include "extension.h"

void calcCoordDouble(Extension& G, Element& Xv, Element& Yv, Element& Xfa, Element& Yfa, Element& Yfb);
void calcCoordAdd(Extension& G, Element& Xv, Element& Yv, Element& Xp, Element& Yp, Element& Xfa, Element& Yfa, Element& Yfb);

void calcFinalExp(Extension& F);

void calcF4mFinalPow(Extension& R, Extension& E);

void calcF2mMult(Element& Ra, Element& Rb, Element& Aa, Element& Ab, Element& Ba, Element& Bb);
void calcF2mInverse(Element& Ea, Element& Eb);

void testCases();
void calcDouble(Element& Ra, Element& Rb, Element& Sa, Element& Sb);
void calcAdd(Element& Ra, Element& Rb, Element& Sa, Element& Sb, Element& Ta, Element& Tb);

#endif
