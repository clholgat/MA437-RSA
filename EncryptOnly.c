#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#define TRUE 1
#define FALSE 0

int encode(mpz_t a, mpz_t n, int blockSize, FILE *fp);

int main(int argc, char *argv[]){
	
	mpz_t n;
	mpz_init_set_str(n, "200033699955714283345172521584008468989639", 10); 
	mpz_mul(n, p, q);
	
	
	mpz_t a;
	mpz_init_set_str(a, "10098768900987679000910003", 10);
	
	int blockSize = 3;
	
	//File to be encrypted
	FILE *fp = fopen("SampleText.txt", "r");
	encode(a, n, blockSize, fp);
	
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
