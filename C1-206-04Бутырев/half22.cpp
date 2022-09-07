/*  BDV   */
#include "mlisp.h"
double root /* 2 */ ( double a, double b );
	 double half__interval /* 14 */ ( double a, double b
	 , double fa, double fb );
	 double __BDV__try /* 26 */ ( double neg__point, double pos__point );
	 bool close__enough_Q /* 40 */ ( double x, double y );
	 double average /* 42 */ ( double x, double y );
	 extern double tolerance /* 44 */ ;
	 extern double total__iterations /* 45 */ ;
	 double f /* 47 */ ( double z );
	 //________________ 
double root /* 2 */ ( double a, double b ) {
 double temp( 0.0 );
	 temp = half__interval( a, b, f( a ), f( b ) );
	 display( "Total number of iterations=" );
	 display( total__iterations );
	 newline();
	 display( "[" );
	 display( a );
	 display( " , " );
	 display( b );
	 display( "]" );
	 return
  temp;
	 }
double half__interval /* 14 */ ( double a, double b
	 , double fa, double fb ) {
 double root( 0.0 );
	 total__iterations = 0.0;
	 root = ( !( !( 0.0 > fa ) || !( fb > 0.0 ) )
	? __BDV__try( a, b )
	: !( !( fa > 0.0 ) || ( fb > 0.0 ) )
	? __BDV__try( b, a )
	: true
	? ( b + 1.0 )
	: _infinity );
	 newline();
	 return
  root;
	 }
double __BDV__try /* 26 */ ( double neg__point, double pos__point ) {
 double midpoint( 0.0 );
	 double test__value( 0.0 );
	 midpoint = average( neg__point, pos__point );
	 display( "+" );
	 total__iterations = ( total__iterations + 1.0 );
	 return
  ( close__enough_Q( neg__point, pos__point )
	? midpoint
	: true
	? ( test__value = f( midpoint ),
	 ( ( test__value > 0.0 )
	? __BDV__try( neg__point, midpoint )
	: ( 0.0 > test__value )
	? __BDV__try( midpoint, pos__point )
	: true
	? midpoint
	: _infinity ) )
	: _infinity );
	 }
bool close__enough_Q /* 40 */ ( double x, double y ) {
 return
  ( tolerance > abs( ( x - y ) ) );
	 }
double average /* 42 */ ( double x, double y ) {
 return
  ( ( x + y ) * ( 1.0 / ( +2.0e0 ) ) );
	 }
double tolerance /* 44 */  = +.001e0;
	 double total__iterations /* 45 */  = 0.0;
	 double f /* 47 */ ( double z ) {
 return
  ( ( ( 2.0 * z * sin( z ) ) - cos( z ) ) + 7.0 );
	 }
int main() {
 display( "Variant 206-04\n" );
	 display( root( 4.0, +5.0e0 ) );
	 newline();
	 display( "(c) Daniil Butyrev 2022\n" );
	 std::cin.get();
	 return
  0;
	 }

