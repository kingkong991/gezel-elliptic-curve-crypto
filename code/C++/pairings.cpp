#include <cstdlib>

#include <time.h>
#include <string>

#include <gmp.h>

#include "pairings.h"

#include "element.h"
#include "extension.h"

bool debug = true;

int main () {
	// Start measuring time
	clock_t start = clock();
	
	//if (!debug)
	//	testCases();
	//exit(0);
		
	// Initialize P & Q values
	mpz_t tmp;
	mpz_init(tmp);
	
	mpz_set_str(tmp, "0x18239FA96047C449DBF0D78A2A596E5A7D67D209F", 0);
	Element Xp = Element(tmp);
	
	mpz_set_str(tmp, "0x421655A1B0BA910F5A1AB8E0C46C3B45F9EE48FC2", 0);
	Element Yp = Element(tmp);
	
	mpz_set_str(tmp, "0x18B05983CBE4AD54B2EA7597DD441ABD8CFD5B3D3", 0);
	Element Xq = Element(tmp);
	
	mpz_set_str(tmp, "0x3D6CB2B7F2C7CDE41B82A65E92D105C2269D1CC75", 0);
	Element Yq = Element(tmp);
	
	// 0x219c4dd67bd0153f2ef5657515304e5140ae767d6
	/*mpz_set_str(tmp, "0x219c4dd67bd0153f2ef5657515304e5140ae767d6", 0);
	Element test = Element(tmp);
	Element test2 = Element(tmp);
	Element test3 = Element(tmp);
	
	printf("[F2m Inv]\n\tA =    ");
	test.print();
	test.inverse(test);
	printf("\tA^-1 = ");
	test.print();
	printf("\tA*A^-1 = ");
	test.multiply(test, test2);
	test.print();*/
		
	//exit(0);*/
	
	// Set modulus
	// Reduction polynomial: x^163 +  x^7  +  x^6  +  x^3  +   1
	// Ignore the x^163, numbers are only 163 bits long
	mpz_t mod;
	mpz_init(mod);
	mpz_set_str(mod, "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011001001", 2);

	// Length of modulus in base 2
	size_t mod_len = 163;
	
	// Calculate distortion map
	Element Xfa = Element(Xq.getMP());
	Element Yfa = Element();
	
	Yfa.add(Xq, Yq);

	Extension F = Extension();

	if (!debug) printf("e(P, Q) = ");

	calcPairing(F, Xp, Yp, Xfa, Yfa);	

	if (!debug) {
		F.print();
	} else {
		printf("s/ %s / colorstartF_e(Fa)_colorend /g\n", mpz_get_str(NULL, 16, F.getA().getMP()));
		printf("s/ %s / colorstartF_e(Fb)_colorend /g\n", mpz_get_str(NULL, 16, F.getB().getMP()));
		printf("s/ %s / colorstartF_e(Fc)_colorend /g\n", mpz_get_str(NULL, 16, F.getC().getMP()));
		printf("s/ %s / colorstartF_e(Fd)_colorend /g\n", mpz_get_str(NULL, 16, F.getD().getMP()));
	}	
	if (!debug) {
		printf("\ne(P, Q)^2 = ");
		F.square(F);		F.print();

		printf("\ne(2P, Q) = ");
		calcDouble(Xp, Yp, Xp, Yp);
		calcPairing(F, Xp, Yp, Xfa, Yfa);			F.print();
	}

	if (debug) {
		printf("s/colorstartB_/\\x1B[34;1m/g\n");
		printf("s/colorstartF_/\\x1B[31;1m/g\n");
		printf("s/colorstartR_/\\x1B[31;1m/g\n");
		printf("s/colorstart_/\\x1B[34;1m/g\n");

		printf("s/_colorend/\\x1B[m/g\n");
	}

	if (!debug) printf("\nTime elapsed: %.3fs\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	exit(0);
}

void calcPairing(Extension& F, Element& Xp, Element& Yp, Element& Xfa, Element& Yfa) {
	// Init f & V
	F.setA(1);
	F.setB(0);
	F.setC(0);
	F.setD(0);

	
	Element Xv = Element(Xp.getMP());
	Element Yv = Element(Yp.getMP());
	
	Element Yfb = Element(Xfa.getMP());

	// Create G
	Extension G = Extension();
		
	// Start Miller loop
	for (int i = 162; i >= 0; i--) {
		F.square(F);
		calcCoordDouble(G, Xv, Yv, Xfa, Yfa, Yfb);
		F.multiply(F, G);
		
		if (debug & 0) {
			printf("s/ %s / colorstart_Xv_%d_colorend /g\n", mpz_get_str(NULL, 16, Xv.getMP()), i);
			printf("s/ %s / colorstart_Yv_%d_colorend /g\n", mpz_get_str(NULL, 16, Yv.getMP()), i);

			printf("s/ %s / colorstart_Ga_%d_colorend /g\n", mpz_get_str(NULL, 16, G.getA().getMP()), i);
			printf("s/ %s / colorstart_Gb_%d_colorend /g\n", mpz_get_str(NULL, 16, G.getB().getMP()), i);

			printf("s/ %s / colorstart_Fa_%d_colorend /g\n", mpz_get_str(NULL, 16, F.getA().getMP()), i);
			printf("s/ %s / colorstart_Fb_%d_colorend /g\n", mpz_get_str(NULL, 16, F.getB().getMP()), i);
			printf("s/ %s / colorstart_Fc_%d_colorend /g\n", mpz_get_str(NULL, 16, F.getC().getMP()), i);
			printf("s/ %s / colorstart_Fd_%d_colorend /g\n", mpz_get_str(NULL, 16, F.getD().getMP()), i);
		} else {/*
			printf("[Miller]  i: %d\n   Xv: ", i);
			Xv.print();
			printf("   Yv: ");
			Yv.print();
			printf("   G: ");
			G.printL();
			printf("   F: ");
			F.printL();
			printf("\n");*/
		}

		if (i == 82) {
			calcCoordAdd(G, Xv, Yv, Xp, Yp, Xfa, Yfa, Yfb);

			Extension R = Extension();
			//calcMultFG(R, F, G);

			F.multiply(F, G);

			//R.print();
			//printf("\n");
			//F.print();

	//exit(0);

			if (debug & 0) {
				printf("s/ %s / colorstart_Xv_%dA_colorend /g\n", mpz_get_str(NULL, 16, Xv.getMP()), i);
				printf("s/ %s / colorstart_Yv_%dA_colorend /g\n", mpz_get_str(NULL, 16, Yv.getMP()), i);

				printf("s/ %s / colorstart_Ga_%dA_colorend /g\n", mpz_get_str(NULL, 16, G.getA().getMP()), i);
				printf("s/ %s / colorstart_Gb_%dA_colorend /g\n", mpz_get_str(NULL, 16, G.getB().getMP()), i);

				printf("s/ %s / colorstart_Fa_%dA_colorend /g\n", mpz_get_str(NULL, 16, F.getA().getMP()), i);
				printf("s/ %s / colorstart_Fb_%dA_colorend /g\n", mpz_get_str(NULL, 16, F.getB().getMP()), i);
				printf("s/ %s / colorstart_Fc_%dA_colorend /g\n", mpz_get_str(NULL, 16, F.getC().getMP()), i);
				printf("s/ %s / colorstart_Fd_%dA_colorend /g\n", mpz_get_str(NULL, 16, F.getD().getMP()), i);
			} else {/*		
				printf("[Coord Add]  i: %d\n   Xv: ", i);
				Xv.print();
				printf("   Yv: ");
				Yv.print();
				printf("   F: ");
				F.printL();
				printf("\n");*/
			}
		}
	}

	//printf("F (before final exp):\n");
	//F.print();
		
	// Calculate final exponentiation
	calcFinalExp(F);
}

void calcMultFG(Extension& R, Extension& F, Extension& G) {
	Element Ra, Rb, Rc, Rd, tmp;

	Ra.multiply(F.getA(), G.getA());
	Ra.add(Ra, F.getD());

	Rb.add(F.getA(), F.getB());
	tmp.add(G.getA(), G.getB());
	Rb.multiply(Rb, tmp);
	Rb.add(Rb, Ra);
	Rb.add(Rb, F.getC());

	tmp.multiply(F.getB(), G.getB());
	Ra.add(Ra, tmp);

	Rc.multiply(F.getC(), G.getA());
	Rc.add(Rc, F.getB());

	Rd.add(F.getC(), F.getD());
	tmp.add(G.getA(), G.getB());
	Rd.multiply(Rd, tmp);
	Rd.add(Rd, Rc);
	Rd.add(Rd, F.getA());
	Rd.add(Rd, F.getD());

	Rc.add(Rc, F.getC());
	tmp.multiply(F.getD(), G.getB());
	Rc.add(Rc, tmp);

	// Stupid way
	/*
	Ra.multiply(F.getA(), G.getA());
	tmp.multiply(F.getB(), G.getB());
	Ra.add(Ra, tmp);
	Ra.add(Ra, F.getD());

	Rb.multiply(F.getA(), G.getB());
	tmp.multiply(F.getB(), G.getA());
	Rb.add(Rb, tmp);
	tmp.multiply(F.getB(), G.getB());
	Rb.add(Rb, tmp);
	Rb.add(Rb, F.getC());
	Rb.add(Rb, F.getD());

	Rc.add(F.getB(), F.getC());
	tmp.multiply(F.getC(), G.getA());
	Rc.add(Rc, tmp);
	tmp.multiply(F.getD(), G.getB());
	Rc.add(Rc, tmp);

	Rd.add(F.getA(), F.getB());
	Rd.add(Rd, F.getD());
	tmp.multiply(F.getC(), G.getB());
	Rd.add(Rd, tmp);
	tmp.multiply(F.getD(), G.getA());
	Rd.add(Rd, tmp);
	tmp.multiply(F.getD(), G.getB());
	Rd.add(Rd, tmp);
	*/

	// Set result
	R.setA(Ra);
	R.setB(Rb);
	R.setC(Rc);
	R.setD(Rd);
}

void testCases() {
	// Initialize P & Q values
	mpz_t tmp;
	mpz_init(tmp);
	
	mpz_set_str(tmp, "0x18239FA96047C449DBF0D78A2A596E5A7D67D209F", 0);
	Element Xp = Element(tmp);
	
	mpz_set_str(tmp, "0x421655A1B0BA910F5A1AB8E0C46C3B45F9EE48FC2", 0);
	Element Yp = Element(tmp);
	
	mpz_set_str(tmp, "0x18B05983CBE4AD54B2EA7597DD441ABD8CFD5B3D3", 0);
	Element Xq = Element(tmp);
	
	mpz_set_str(tmp, "0x3D6CB2B7F2C7CDE41B82A65E92D105C2269D1CC75", 0);
	Element Yq = Element(tmp);
	
	// Base points
	printf("[Base Points]\n   P:\n     X: ");
	Xp.print();
	printf("     Y: ");
	Yp.print();
	printf("   Q:\n     X: ");
	Xq.print();
	printf("     Y: ");
	Yq.print();
	printf("\n");
	
	// Doubling test
	Element DblA = Element();
	Element DblB = Element();
	
	calcDouble(DblA, DblB, Xp, Yp);
	
	printf("[2*P]\n   Xn:\t");
	DblA.print();
	printf("   Yn:\t");
	DblB.print();
	printf("\n");
	
	// Add test
	Element AddA = Element();
	Element AddB = Element();
	
	calcAdd(AddA, AddB, Xp, Yp, Xq, Yq);
	
	printf("[P+Q]\n   Xn:\t");
	AddA.print();
	printf("   Yn:\t");
	AddB.print();
	printf("\n");

	// F(2^m) Addition test
	Element add = Element();
	
	add.add(Xq, Yq);
	
	printf("[Fm Add]\n   R:\t");
	add.print();
	printf("\n");
	
	// F(2^m) Multiplication test
	Element mult = Element();
	
	mult.multiply(Xp, Yp);
	
	printf("[Fm Mult]\n   R:\t");
	mult.print();
	printf("\n");

	// F(2^m) Inverse test
	Element inv = Element();
	
	inv.inverse(Xp);
	
	printf("[Fm Inv]\n   R:\t");
	inv.print();
	printf("\n");
	
	// F(2^(2*m)) Multiplication test
	Element F2mMa = Element();
	Element F2mMb = Element();
	
	F2mMa.set(Xp);
	F2mMb.set(Yp);
	
	calcF2mMult(F2mMa, F2mMb, Xp, Yp, Xq, Yq);
	
	printf("[F2m Mult]\n  F2mX:\t");
	F2mMa.print();
	printf("  F2mY:\t");
	F2mMb.print();
	printf("\n");
	
	// F(2^(2*m)) Square test
	Element F2mSa = Element();
	Element F2mSb = Element();
	
	F2mSa.set(Xp);
	F2mSb.set(Yp);
	
	calcF2mMult(F2mSa, F2mSb, Xp, Yp, Xp, Yp);
	
	printf("[F2m Square]\n  F2mX:\t");
	F2mSa.print();
	printf("  F2mY:\t");
	F2mSb.print();
	printf("\n");
	
	// F(2^(2*m)) Inverse test
	Element F2mIa = Element();
	Element F2mIb = Element();
	
	F2mIa.set(Xp);
	F2mIb.set(Yp);
	
	calcF2mInverse(F2mIa, F2mIb);
	
	printf("[F2m Inv]\n  F2mX:\t");
	F2mIa.print();
	printf("  F2mY:\t");
	F2mIb.print();
	printf("\n");

	// F(2^(4*m)) Multiplication test
	Extension F4mMa = Extension(Xp, Yp, Xq, Yq);	
	Extension F4mMb = Extension(Xq, Yq, Xp, Yp);	
	
	F4mMa.multiply(F4mMa, F4mMb);
	
	printf("[F4m Mult]\n   F4mM:");
	F4mMa.print();
	printf("\n");	

	// F(2^(4*m)) Square test
	Extension F4mS = Extension(Xp, Yp, Xq, Yq);	
	
	F4mS.square(F4mS);
	
	printf("[F4m Square]\n   F4mS:");
	F4mS.print();
	printf("\n");
}

void calcDouble(Element& Ra, Element& Rb, Element& Sa, Element& Sb) {
	Element lambda = Element();
	
	lambda.square(Sa);
	lambda.addOne();
	
	// Calculate new X & Y coords
	Element Xnew = Element();
	Element Ynew = Element();
	
	Xnew.square(lambda);
	
	Ynew.add(Xnew, Sa);
	Ynew.multiply(Ynew, lambda);
	Ynew.add(Ynew, Sb);
	Ynew.addOne();
	
	// Set new coords
	Ra.set(Xnew);
	Rb.set(Ynew);	
}

void calcAdd(Element& Ra, Element& Rb, Element& Sa, Element& Sb, Element& Ta, Element& Tb) {
	Element lambda = Element();
	
	lambda.add(Sa, Ta);
		
	lambda.inverse(lambda);
	
	Element temp = Element();
	temp.add(Sb, Tb);
	
	lambda.add(lambda, temp);
	
	// Calculate new X & Y coords
	Element Xnew = Element();
	Element Ynew = Element();
	
	Xnew.square(lambda);
	Xnew.add(Xnew, Sa);
	Xnew.add(Xnew, Ta);
	
	Ynew.add(Xnew, Ta);
	Ynew.multiply(Ynew, lambda);
	Ynew.add(Ynew, Tb);
	Ynew.addOne();
	
	// Set new coords
	Ra.set(Xnew);
	Rb.set(Ynew);
}

void calcCoordDouble(Extension& G, Element& Xv, Element& Yv, Element& Xfa, Element& Yfa, Element& Yfb) {
	Element lambda = Element();
	
	lambda.square(Xv);
	lambda.addOne();
	
	// Calculate new X & Y coords
	Element Xnew = Element();
	Element Ynew = Element();
	
	Xnew.square(lambda);
	
	Ynew.add(Xnew, Xv);
	Ynew.multiply(Ynew, lambda);
	Ynew.add(Ynew, Yv);
	Ynew.addOne();
	
	// Calculate G
	G.getA().add(Xv, Xfa);
	G.getA().multiply(G.getA(), lambda);
	G.getA().add(G.getA(), Yv);
	G.getA().add(G.getA(), Yfa);
	
	G.getB().add(lambda, Yfb);
	
	G.getC().set(0);
	
	G.getD().set(1);
	
	// Set new coords
	Xv.set(Xnew);
	Yv.set(Ynew);	
}

void calcCoordAdd(Extension& G, Element& Xv, Element& Yv, Element& Xp, Element& Yp, Element& Xfa, Element& Yfa, Element& Yfb) {
	Element lambda = Element();
	
	lambda.add(Xv, Xp);
	
/*	printf("Xv =      ");
	Xv.print();
	printf("Xp =      ");
	Xp.print();
	printf("Xv + Xp = ");
	lambda.print();
	printf("\n");*/
	
	lambda.inverse(lambda);
	
/*	printf("inv =     ");
	lambda.print();
	printf("\n");*/

	Element temp = Element();
	temp.add(Yv, Yp);
	
/*	printf("Yv =      ");
	Yv.print();
	printf("Yp =      ");
	Yp.print();
	printf("Yv + Yp = ");
	temp.print();
	printf("\n");
	
	printf("final lambda calc: ");
	lambda.print();
	temp.print();

	printf(" product = ");*/

	lambda.multiply(lambda, temp);

//	printf("lambda =  ");
//	lambda.print();
//	printf("\n");
	
	// Calculate new X & Y coords
	Element Xnew = Element();
	Element Ynew = Element();
	
	Xnew.square(lambda);
	Xnew.add(Xnew, Xv);
	Xnew.add(Xnew, Xp);
	
	Ynew.add(Xnew, Xp);
	Ynew.multiply(Ynew, lambda);
	Ynew.add(Ynew, Yp);
	Ynew.addOne();
	
	// Calculate G
	G.getA().add(Xp, Xfa);
	G.getA().multiply(G.getA(), lambda);
	G.getA().add(G.getA(), Yp);
	G.getA().add(G.getA(), Yfa);
	
	G.getB().add(lambda, Yfb);
	
	G.getC().set(0);
	
	G.getD().set(1);
	
	// Set new coords
	Xv.set(Xnew);
	Yv.set(Ynew);
}

void calcFinalExp(Extension& F) {
	// Calculate some temporary variables
	Element temp = Element();
	
	Element m0, m1, m2, m3;
	
	m0.square(F.getA());
	m1.square(F.getB());
	m2.square(F.getC());
	m3.square(F.getD());
	
	Element T0a, T0b, T1a, T1b, T2a, T2b, T3a, T3b;
	
	T0a.add(m0, m1);
	T0b.set(m1);
	
	T1a.add(m2, m3);
	T1b.set(m3);
	
	T2a.set(m3);
	T2b.set(m2);
	
	// Use T3a & T3b as temp here
	T3a.add(F.getA(), F.getB());
	temp.add(F.getC(), F.getD());
	// T3a = a0
	T3a.multiply(T3a, temp);
	// T3b = a1
	T3b.multiply(F.getA(), F.getC());
	// temp = a2
	temp.multiply(F.getB(), F.getD());
	
	T3a.add(T3a, temp);
	T3b.add(T3b, temp);
	
	Element T4a, T4b;
	
	T4b.add(m1, m3);
	T4a.add(T4b, m0);
	T4a.add(T4a, m2);
	
	Element T6a, T6b, T7a, T7b, T8a, T8b;
	
	T6a.set(m2);
	T6b.add(m2, m3);
	
	T7a.set(T4a);
	T7b.set(T4b);
	
	T8a.set(T0a);
	T8b.set(T0b);
	
	Element Da, Db;
	
	Da.add(T3a, T4a);
	Db.add(T3b, T4b);
	
	if (debug) {
		//printf("s/ %s / colorstartB_m0_colorend /g\n", mpz_get_str(NULL, 16, m0.getMP()));
		//printf("s/ %s / colorstartB_m1_colorend /g\n", mpz_get_str(NULL, 16, m1.getMP()));
		//printf("s/ %s / colorstartB_m2_colorend /g\n", mpz_get_str(NULL, 16, m2.getMP()));
		//printf("s/ %s / colorstartB_m3_colorend /g\n", mpz_get_str(NULL, 16, m3.getMP()));

		//printf("s/ %s / colorstartB_T6a_colorend /g\n", mpz_get_str(NULL, 16, T6a.getMP()));
		//printf("s/ %s / colorstartB_T6b_colorend /g\n", mpz_get_str(NULL, 16, T6b.getMP()));

		//printf("s/ %s / colorstartB_T7a_colorend /g\n", mpz_get_str(NULL, 16, T7a.getMP()));
		//printf("s/ %s / colorstartB_T7b_colorend /g\n", mpz_get_str(NULL, 16, T7b.getMP()));

		//printf("s/ %s / colorstartB_T8a_colorend /g\n", mpz_get_str(NULL, 16, T8a.getMP()));
		//printf("s/ %s / colorstartB_T8b_colorend /g\n", mpz_get_str(NULL, 16, T8b.getMP()));

		//printf("s/ %s / colorstartB_Da_colorend /g\n", mpz_get_str(NULL, 16, Da.getMP()));
		//printf("s/ %s / colorstartB_Db_colorend /g\n", mpz_get_str(NULL, 16, Db.getMP()));
	}
		
	// Calculate inverse of D
	calcF2mInverse(Da, Db);
	
	if (debug) {
		/*
		printf("s/ %s / colorstartB_DaI_colorend /g\n", mpz_get_str(NULL, 16, Da.getMP()));
		printf("s/ %s / colorstartB_DbI_colorend /g\n", mpz_get_str(NULL, 16, Db.getMP()));
		*/
	}
	
	// Calculate V & W
	
	Element V0a, V0b, W0a, W0b;
	Element V1a, V1b, W1a, W1b;
	
	V0a.add(T6a, T8a);
	V0b.add(T6b, T8b);
	
	V1a.set(T6a);
	V1b.set(T6b);
	
	W0a.set(T7a);
	W0b.set(T7b);
	
	W1a.set(T6a);
	W1b.set(T6b);

	if (debug) {
		/*
		printf("s/ %s / colorstartB_V0a_colorend /g\n", mpz_get_str(NULL, 16, V0a.getMP()));
		printf("s/ %s / colorstartB_V0b_colorend /g\n", mpz_get_str(NULL, 16, V0b.getMP()));

		printf("s/ %s / colorstartB_V1a_colorend /g\n", mpz_get_str(NULL, 16, V1a.getMP()));
		printf("s/ %s / colorstartB_V1b_colorend /g\n", mpz_get_str(NULL, 16, V1b.getMP()));

		printf("s/ %s / colorstartB_W0a_colorend /g\n", mpz_get_str(NULL, 16, W0a.getMP()));
		printf("s/ %s / colorstartB_W0b_colorend /g\n", mpz_get_str(NULL, 16, W0b.getMP()));
		*/
	}

	calcF2mMult(V0a, V0b, V0a, V0b, Da, Db);
	calcF2mMult(V1a, V1b, V1a, V1b, Da, Db);
	
	calcF2mMult(W0a, W0b, W0a, W0b, Da, Db);
	calcF2mMult(W1a, W1b, W1a, W1b, Da, Db);

	if (debug) {
		//printf("s/ %s / colorstartB_u0_colorend /g\n", mpz_get_str(NULL, 16, V0a.getMP()));
		//printf("s/ %s / colorstartB_u1_colorend /g\n", mpz_get_str(NULL, 16, V0b.getMP()));

		printf("s/ %s / colorstartB_W1aD_colorend /g\n", mpz_get_str(NULL, 16, V1a.getMP()));
		printf("s/ %s / colorstartB_W1bD_colorend /g\n", mpz_get_str(NULL, 16, V1b.getMP()));

		printf("s/ %s / colorstartB_W0aD_colorend /g\n", mpz_get_str(NULL, 16, W0a.getMP()));
		printf("s/ %s / colorstartB_W0bD_colorend /g\n", mpz_get_str(NULL, 16, W0b.getMP()));
	}
		
	Extension V = Extension(V0a, V0b, V1a, V1b);
	Extension W = Extension(W0a, W0b, W1a, W1b);
		
	// Calculate V^(2^m + 1)
	calcF4mFinalPow(V, V);

	if (debug) {
		printf("s/ %s / colorstartB_Va_colorend /g\n", mpz_get_str(NULL, 16, V.getA().getMP()));
		printf("s/ %s / colorstartB_Vb_colorend /g\n", mpz_get_str(NULL, 16, V.getB().getMP()));
		printf("s/ %s / colorstartB_Vc_colorend /g\n", mpz_get_str(NULL, 16, V.getC().getMP()));
		printf("s/ %s / colorstartB_Vd_colorend /g\n", mpz_get_str(NULL, 16, V.getD().getMP()));
	}
	
	// Calculate W^(2^82)
	for (int i = 0; i < 82; i++) {
	/*
		if (debug & i == 0) {
			Element m0, m1, m2, m3;

			m0.square(W.getA());
			m1.square(W.getB());
			m2.square(W.getC());
			m3.square(W.getD());

			Element s0a;

			s0a.add(m0, m1);

			printf("s/ %s / colorstartB_s0'_colorend /g\n", mpz_get_str(NULL, 16, s0a.getMP()));

			printf("s/ %s / colorstartB_m0_colorend /g\n", mpz_get_str(NULL, 16, m0.getMP()));
			printf("s/ %s / colorstartB_m1_colorend /g\n", mpz_get_str(NULL, 16, m1.getMP()));
			printf("s/ %s / colorstartB_m3_colorend /g\n", mpz_get_str(NULL, 16, m3.getMP()));
		}
		*/

		W.square(W);

		if (debug & i == 0) {
			/*
			printf("s/ %s / colorstartB_s0_colorend /g\n", mpz_get_str(NULL, 16, W.getA().getMP()));
			printf("s/ %s / colorstartB_s1_colorend /g\n", mpz_get_str(NULL, 16, W.getB().getMP()));
			printf("s/ %s / colorstartB_s2_colorend /g\n", mpz_get_str(NULL, 16, W.getC().getMP()));
			printf("s/ %s / colorstartB_s3_colorend /g\n", mpz_get_str(NULL, 16, W.getD().getMP()));
			*/
		}
	}

	if (debug) {
		printf("s/ %s / colorstartB_WaS_colorend /g\n", mpz_get_str(NULL, 16, W.getA().getMP()));
		printf("s/ %s / colorstartB_WbS_colorend /g\n", mpz_get_str(NULL, 16, W.getB().getMP()));
		printf("s/ %s / colorstartB_WcS_colorend /g\n", mpz_get_str(NULL, 16, W.getC().getMP()));
		printf("s/ %s / colorstartB_WdS_colorend /g\n", mpz_get_str(NULL, 16, W.getD().getMP()));
	}
	
	// Calculate F = V*W
	F.multiply(V, W);
}

void calcF4mFinalPow(Extension& R, Extension& E) {
	// Calculate some temporary variables
	Element m0, m1, m2, m3, m4;
	Element s0, s1;
	
	s0.add(E.getC(), E.getD());
	s1.add(E.getA(), E.getB());

	if (debug) {
		//printf("s/ %s / colorstartR_m0\"_colorend /g\n", mpz_get_str(NULL, 16, s0.getMP()));
		//printf("s/ %s / colorstartR_m0'_colorend /g\n", mpz_get_str(NULL, 16, s1.getMP()));
	}	
	
	m0.multiply(s0, s1);
	m1.multiply(E.getC(), E.getD());
	m2.multiply(E.getA(), E.getD());
	m3.multiply(E.getA(), E.getB());
	m4.multiply(E.getB(), E.getC());
	
	s0.square(s0);
	s1.square(s1);

	if (debug) {
		/*
		printf("s/ %s / colorstartR_m0_colorend /g\n", mpz_get_str(NULL, 16, m0.getMP()));
		printf("s/ %s / colorstartR_m1_colorend /g\n", mpz_get_str(NULL, 16, m1.getMP()));
		printf("s/ %s / colorstartR_m2_colorend /g\n", mpz_get_str(NULL, 16, m2.getMP()));
		printf("s/ %s / colorstartR_m3_colorend /g\n", mpz_get_str(NULL, 16, m3.getMP()));
		printf("s/ %s / colorstartR_m4_colorend /g\n", mpz_get_str(NULL, 16, m4.getMP()));

		printf("s/ %s / colorstartR_s0_colorend /g\n", mpz_get_str(NULL, 16, s0.getMP()));
		printf("s/ %s / colorstartR_s1_colorend /g\n", mpz_get_str(NULL, 16, s1.getMP()));
		*/
	}
	
	// Calculate result
	R.getC().add(m1, s0);
	
	R.getB().add(R.getC(), m0);

	if (debug) {
		//printf("s/ %s / colorstartR_r0'_colorend /g\n", mpz_get_str(NULL, 16, R.getB().getMP()));
	}

	R.getA().add(R.getB(), s1);
	R.getA().add(R.getA(), m2);
	R.getA().add(R.getA(), m3);
	
	R.getB().add(R.getB(), m4);
	
	R.getD().add(m0, m2);
}

void calcF2mMult(Element& Ra, Element& Rb, Element& Aa, Element& Ab, Element& Ba, Element& Bb) {
	// Calculate some temporary variables
	Element a0, a1, a2;
	
	// Use a1 as temp var
	a0.add(Aa, Ab);
	a1.add(Ba, Bb);
	a0.multiply(a0, a1);
	
	a1.multiply(Aa, Ba);
	
	a2.multiply(Ab, Bb);
	
	// Calculate result
	Ra.add(a1, a2);
	Rb.add(a0, a1);
}

void calcF2mInverse(Element& Ea, Element& Eb) {
	// Calculate some temporary variables
	Element w, temp;
	
	temp.square(Ea);

	w.add(Ea, Eb);
	w.multiply(w, Eb);
	w.add(w, temp);
		
	w.inverse(w);
	
	// Calculate result
	Element Ra, Rb;
	
	Ea.add(Ea, Eb);
	Ea.multiply(Ea, w);
	
	Eb.multiply(Eb, w);	
}
