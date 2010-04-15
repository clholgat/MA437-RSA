#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#define TRUE 1
#define FALSE 0

int checkSystem(mpz_t p, mpz_t q, mpz_t a, mpz_t b, mpz_t n, mpz_t m);
int encode(mpz_t a, mpz_t n, int blockSize, FILE *fp);
int decode(mpz_t b, mpz_t n, int blockSize, FILE *fq);

int main(int argc, char *argv[]){
	mpz_t p;
	mpz_init_set_str(p, "400043344212007458013", 10);
	
	mpz_t q;
	mpz_init_set_str(q, "500030066366269001203", 10);
	
	mpz_t n;
	mpz_init(n); 
	mpz_mul(n, p, q);
	gmp_printf("%Zd", n);
	
	mpz_t m, qq, pp;
	mpz_init(m);
	mpz_init(qq);
	mpz_init(pp);
	mpz_sub_ui(qq, q, 1);
	mpz_sub_ui(pp, p, 1);	
	mpz_mul(m, pp, qq);
	
	mpz_t a;
	mpz_init_set_str(a, "10098768900987679000910003", 10);
	
	mpz_t b;
	mpz_init(b);
	mpz_invert(b, a, m);
	
	checkSystem(p, q, a, b, n, m);
	
	int blockSize = 3;
	
	//File to be encrypted
	FILE *fp = fopen("SampleText.txt", "r");
	encode(a, n, blockSize, fp);
	
	//File to be decrypted
	FILE *fq = fopen("encrypted.txt", "r");
	decode(b, n, blockSize, fq);

	return 1;
}

int checkSystem(mpz_t p, mpz_t q, mpz_t a, mpz_t b, mpz_t n, mpz_t m){
	assert( mpz_probab_prime_p(p, 10) != 0);
	assert( mpz_probab_prime_p(q, 10) != 0);
	
	mpz_t gcd;
	mpz_init(gcd);	assert( mpz_probab_prime_p(q, 10) != 0);
	mpz_gcd(gcd, a, m);
	assert( mpz_cmp_ui(gcd, 1) == 0);
	mpz_clear(gcd);
	
	mpz_t abCheck;
	mpz_init(abCheck);
	mpz_mul(abCheck, a, b);
	mpz_powm_ui(abCheck, abCheck, 1, m);
	assert( mpz_cmp_ui(abCheck, 1) == 0);
	mpz_clear(abCheck);
	
	mpz_t pqCheck;
	mpz_init(pqCheck);
	mpz_mul(pqCheck, p, q);
	assert( mpz_cmp(pqCheck, n) == 0);
	
	return TRUE;
}
	
	 

int encode(mpz_t a, mpz_t n, int blockSize, FILE *fp){
	FILE *fq = fopen("encrypted.txt", "w+");	

	mpz_t block;	
	int x[blockSize];
	int done = FALSE;
	while(!done){
		mpz_init(block);
		for( int i = 0; i < blockSize; i++ ){
			x[i] = fgetc(fp);
			if( x[i] == EOF){			
				for( int j = i; j<blockSize; j++){
					x[j] = 0;
					done = TRUE;
				}
				break;
			}
		}
		for( int i = 0; i < blockSize; i++ ){
			mpz_add_ui(block, block, (unsigned long) x[i]);
			if( i < (blockSize-1)){
				mpz_mul_2exp(block, block, (unsigned long) CHAR_BIT);
			}
		}
		
		mpz_powm(block, block, a, n);
		mpz_out_str(fq, 16, block);
		fprintf(fq, "\n");
		
		mpz_clear(block);
	}
	
	
	fclose(fq);
	return TRUE;
}

int decode(mpz_t b, mpz_t n, int blockSize, FILE *fq){
	FILE *fr = fopen("decrypted.txt", "w+");
	assert(fr != NULL);
	mpz_t y;
	mpz_init(y);
	
	mpz_t scanner;
	mpz_init(scanner);
	
	mpz_t mask;
	unsigned long maskbits = pow(2, CHAR_BIT) -1;
	mpz_init_set_ui(mask, maskbits);
	mpz_t chunk;
	
	//int done = FALSE;
	int x[blockSize];
	
	while(!feof(fq)){
		mpz_init(chunk);
		gmp_fscanf(fq, "%Zx", scanner);
		mpz_powm(y, scanner, b, n);
		for( int i = 0; i < blockSize; i++){
			mpz_and(chunk, mask, y);
			x[i] = (int)mpz_get_ui(chunk);
			mpz_tdiv_q_2exp(y, y, (unsigned long) CHAR_BIT);
		}	
		for( int i = (blockSize -1); i >= 0; i--){
			fprintf(fr, "%c", x[i]);
		}
		
		mpz_clear(chunk);
	}
	return TRUE;
}

		 
				
	
