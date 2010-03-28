#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int n;
	int a;
	int block_size;
	char file;
	} Profile;
	
Profile load(FILE *fp){
	Profile profile1;
	
	fscanf( fp, "n = %d", &profile1.n);
	fscanf( fp, "a = %d", &profile1.a);
	fscanf( fp, "block size = %d", &profile1.block_size);
	fscanf( fp, "file = %s", &profile1.file);
	
	return profile1;
	}
	

