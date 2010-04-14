#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>
 
void new_xab(mpz_t x, mpz_t a, mpz_t b, mpz_t beta, mpz_t g, mpz_t P, mpz_t Zp); 

int main(int argc, char *argv[]){
	mpz_t P, Zp, g, beta, x, X, a, A, b, B;
	
	mpz_init_set_str(P, "1019", 10);
	
	mpz_init(Zp);
	mpz_sub_ui(Zp, P, 1);
	
	mpz_init_set_str(g, "2", 10);
	
	mpz_init_set_str(beta, "5", 10);
	
	mpz_init_set_str(x, "1", 10);
	mpz_init_set_str(X, "1", 10);
	mpz_init(a);
	mpz_init(A);
	mpz_init(b);
	mpz_init(B);

   	for( int i = 1; mpz_cmp_ui(Zp, (unsigned long) i) > 0; ++i ) {
     		new_xab( x, a, b, beta, g, P, Zp );
     		new_xab( X, A, B, beta, g, P, Zp ); 
     		new_xab( X, A, B, beta, g, P, Zp );
     		printf( "%x  %Zx %Zx %Zx  %Zx %Zx %Zx\n", i, x, a, b, X, A, B );
     		if( !mpz_cmp(x, X) ){ 
     			break;
   		}
   	}
   	return 0;
}

void new_xab( mpz_t x, mpz_t a, mpz_t b, mpz_t beta, mpz_t g, mpz_t P, mpz_t Zp ) {
  	mpz_t switchTest;
   	mpz_init(switchTest);
   	
   	mpz_mod_ui(switchTest, x, 3);
   	
   	int test = (int)mpz_get_ui(switchTest);
   
   	switch( test ) {
   	case 0: 
   		mpz_powm_ui(x, x, 2, P);
   		
   		mpz_mul_ui(a, a, 2);
   		mpz_mod(a, a, Zp);
   		
   		mpz_mul_ui(b, b, 2);
   		mpz_mod(b, b, Zp);  
   		break;
   	
   	case 1: 
   		mpz_mul(x, x, g);
   		mpz_mod(x, x, P);
   		
   		mpz_add_ui(a, a, 1);
   		mpz_mod(a, a, Zp);
   		break;
   		
   	case 2: 
   		mpz_mul(x, x, beta);
   		mpz_mod(x, x, P);
   		
   		mpz_add_ui(b, b, 1);
   		mpz_mod(b, b, Zp);  
   		break;
  	}
 }
 
