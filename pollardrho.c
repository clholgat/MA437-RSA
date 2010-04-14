#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>
 
void new_xab(int& x, int& a, int& b, int beta, int g); 

 int main(void) {
  int P = 1019, Zp = P - 1;  
  int g = 2;            
  int beta = 5;   


   int x=1, a=0, b=0;
   int X=x, A=a, B=b;
   int i;
   for( i = 1; i < Zp; ++i ) {
     new_xab( x, a, b, beta, g );
     new_xab( X, A, B, beta, g ); new_xab( X, A, B, beta, g );
     printf( "%3d  %4d %3d %3d  %4d %3d %3d\n", i, x, a, b, X, A, B );
     if( x == X ) break;
   }
   return 0;
 }

 void new_xab( int& x, int& a, int& b, int beta, int g ) {
   switch( x%3 ) {
   case 0: x = (x*x)% P;  a =  a*2  % Zp;  b =  b*2  % n;  break;
   case 1: x = (x*g)% P;  a = (a+1) % Zp;                  break;
   case 2: x = (x*beta)% P;                  b = (b+1) % n;  break;
   }
 }
 
