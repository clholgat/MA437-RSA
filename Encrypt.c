#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef long long unsigned int Block;
typedef long long unsigned int BigInt;

int abCheck(int a, int b, int m);
int encode(int a, BigInt n, int blockSize, FILE *fp);
int decode(int b, BigInt n, int blockSize, FILE *fq);
BigInt largePow(BigInt x, BigInt c, BigInt n);

int main(int argc, char *argv[]){
	int p = 79;
	int q = 151;
	BigInt n = p*q;
	//printf("%llu\n", n);
	//int m = (p-1)*(q-1);
	int a = 473;
	int b = 8237;
	int blockSize = 3;
	
	FILE *fp = fopen("Encrypt.c", "r");
	encode(a, n, blockSize, fp);
	
	FILE *fq = fopen("encrypted.txt", "r");
	decode(b, n, blockSize, fq);

	//printf("%d",abCheck(a,b, m));
	
	return 1;
}

int abCheck(int a, int b, int m){
	return (fmod(a*b, m) == 1) ? TRUE: FALSE;
}

int encode(int a, BigInt n, int blockSize, FILE *fp){
	FILE *fq = fopen("encrypted.txt", "w+");	

	Block block = 0;	
	unsigned long int x = 0;
	int done = FALSE;
	while(!done){
		for( int i = 0; i < blockSize; i++ ){
			x = (int)getc(fp);
			//printf("%lu \n", x);
			if( x != (unsigned long)(-1)){			
				block += x;
				//printf("%llx \n", block);
				if(i != (blockSize - 1)){
					block <<= (CHAR_BIT);
				}
			}
			else{
				for( int j = i; j<blockSize; j++){
					block += rand()%255;
					if(j != (blockSize - 1)){
						block <<= (CHAR_BIT);
					}
				}
				done = TRUE;
			}
		}
		fprintf(fq, "%llu ", (BigInt)largePow(x,a,n));
		printf("%d ", (int)block);
		printf("%d \n", (int)largePow(x, a, n));
		block = 0;
	}
	fclose(fq);
	return TRUE;
}

int decode(int b, BigInt n, int blockSize, FILE *fq){
	FILE *fr = fopen("decrypted.txt", "w+");
	
	int y = 0;
	int done = FALSE;
	int chunk = pow(2, CHAR_BIT) -1;
	while(fscanf(fq, "%d", &y) != EOF){
		//printf("Starting decrypt \n");
		if( y != (-1)){
			y =fmod(pow(y, b), n);
			for( int i = 0 ; i < blockSize; i++){
				fprintf(fr, "%c", (char)(y & chunk));
				y >>= (CHAR_BIT*2);
			}
		}else{
			done = TRUE;
		}
	}
	return TRUE;
}

BigInt largePow(BigInt x, BigInt c, BigInt n){
	BigInt bit = 1;
	BigInt runTot = 1;
	
	for(int i = 0; i < (sizeof(c)*2); i++){
		if( (c & bit) != 0){
			runTot *= fmod(pow(x,pow(2,i)), n);
			runTot = fmod(runTot, n);
		}
		bit <<= 1;
		printf("largePow: runTot = %llu \n", runTot);
	}
	return runTot;
}
			 
				
	
