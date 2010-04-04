#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


int abCheck(int a, int b, int m);
int encode(int a, int n, int blockSize, FILE *fp);

int main(int argc, char *argv[]){
	int p = 5;
	int q = 11;
	int n = p*q;
	//int m = (p-1)*(q-1);
	int a = 27;
	//int b = 3;
	int blockSize = 2;
	
	FILE *fp = fopen("Encrypt.c", "r");
	encode(a, n, blockSize, fp);

	//printf("%d",abCheck(a,b, m));
	
	return 1;
}

int abCheck(int a, int b, int m){
	return (fmod(a*b, m) == 1) ? TRUE: FALSE;
}

int encode(int a, int n, int blockSize, FILE *fp){
	FILE *fq = fopen("encrypted.txt", "+w");	

	int block = 0;	
	int x = 0;
	int done = FALSE;
	while(!done){
		for( int i = 0; i < blockSize; i++ ){
			x = (int)getc(fp);
			if( x != -1){			
				block += x;
				block <<= CHAR_BIT;
			}
			else{
				for( int j = i; j<blockSize; j++){
					block += rand()%255;
					block <<= CHAR_BIT;
				}
				done = TRUE;
			}
		}
		fprintf(fq, "%d ", (int)fmod(pow(block,a), n));
		block = 0;
	}
	fclose(fq);
	return TRUE;
}
			
	
