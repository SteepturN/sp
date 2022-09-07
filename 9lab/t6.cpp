/*  BDV   */
#include "mlisp.h"
double __BDV__try/*2*/ (double x);
double f/*3*/ (double x, double y);
//________________ 
double __BDV__try/*2*/ (double x){
 
x = f( x, 2 );
	 return
 x;
	 }

double f/*3*/ (double x, double y){
 return
 expt( x, y );
	 }
int main(){
 display(__BDV__try( 3 ));
	 newline();
	 std::cin.get();
	 return
 0;
	 }

