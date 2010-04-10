#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#define TRUE 1
#define FALSE 0

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
	
	mpz_t m;
	mpz_init(m);
	mpz_mul(m, p-1, q-1);
	
	mpz_t a;
	mpz_init_set_str(a, "10098768900987679000910003", 10);
	
	mpz_t b;
	mpz_init(b);
	mpz_invert(b, a, m);
	
	int blockSize = 1;
	
	FILE *fp = fopen("Encrypt.c", "r");
	encode(a, n, blockSize, fp);
	
	FILE *fq = fopen("encrypted.txt", "r");
	decode(b, n, blockSize, fq);

	return 1;
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
					x[j] = rand()%127;
					done = TRUE;
				}	
			}
		}
		for( int i = 0; i < blockSize; i++ ){
			mpz_add_ui(block, block, (unsigned long) x[i]);
			if( i < (blockSize -1)){
				mpz_mul_2exp(block, block, (unsigned long) CHAR_BIT);
			}
		}
		printf("%d", mpz_cmp(n, block));
		
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
	mpz_t mask;
	unsigned long maskbits = pow(2, CHAR_BIT) -1;
	mpz_init_set_ui(mask, maskbits);
	mpz_t chunk;
	
	int done = FALSE;
	int x[blockSize];
	
	while(!feof(fq)){
		mpz_init(chunk);
		gmp_fscanf(fq, "%Zx", y);
		mpz_powm(y, y, b, n);
		for( int i = 0; i < blockSize; i++){
			mpz_and(chunk, mask, y);
			x[i] = (int)mpz_get_ui(chunk);
			mpz_tdiv_q_2exp(y, y, (unsigned long) CHAR_BIT);
		}	
		for( int i = (blockSize -1); i >= 0; i--){
			fprintf(fr, "%d ", x[i]);
		}
		
		mpz_clear(chunk);
		//done = TRUE;
	}
	return TRUE;
}

		 
				
	
