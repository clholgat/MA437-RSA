#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

#define TRUE 1
#define FALSE 0

int decode(mpz_t b, mpz_t n, int blockSize, FILE *fq);

int main(int argc, char *argv[]){

	mpz_t n;
	mpz_init_set_str(n, "200033699955714283345172521584008468989639", 10); 
	
	mpz_t b;
	mpz_init_set_str(b, "54299300950841826990071853678997985400035", 10);
	
	int blockSize = 3;
	
        //File to be decrypted
	FILE *fq = fopen("encrypted.txt", "r");
	decode(b, n, blockSize, fq);

	return 1;
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

