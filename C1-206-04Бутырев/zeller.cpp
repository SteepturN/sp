/*  BDV   */
#include "mlisp.h"
double day__of__week /* 2 */ (  );
	 double zeller /* 11 */ ( double d, double m
	 , double y, double c );
	 double neg__to__pos /* 21 */ ( double d );
	 double birthday /* 26 */ ( double dw );
	 extern double dd /* 41 */ ;
	 extern double mm /* 42 */ ;
	 extern double yyyy /* 43 */ ;
	 //________________ 
double day__of__week /* 2 */ (  ) {
 return
  zeller( dd, ( 010.0 + ( !( mm > 2.0 )
	? mm
	: true
	? ( mm - 12.0 )
	: _infinity ) ), remainder( ( 1.0 + ( ( 3.0 > mm )
	? ( yyyy - 2.0 )
	: true
	? ( yyyy - 1.0 )
	: _infinity ) ), 100.0 ), quotient( ( !( mm > 2.0 )
	? ( yyyy - 1.0 )
	: true
	? yyyy
	: _infinity ), 100.0 ) );
	 }
double zeller /* 11 */ ( double d, double m
	 , double y, double c ) {
 return
  neg__to__pos( remainder( ( d + y + quotient( ( ( 26.0 * m ) - 2.0 ), 10.0 ) + quotient( y, 4.0 ) + quotient( c, 4.0 ) + ( 2.0 * ( -c ) ) ), 7.0 ) );
	 }
double neg__to__pos /* 21 */ ( double d ) {
 return
  ( ( 0.0 > d )
	? ( d + 7.0 )
	: true
	? d
	: _infinity );
	 }
double birthday /* 26 */ ( double dw ) {
 display( "Daniil Butyrev was born on " );
	 display( ( ( dw == 1.0 )
	? "Monday "
	: ( ( dw == 2.0 )
	? "Tuesday "
	: ( ( dw == 3.0 )
	? "Wednesday "
	: ( ( dw == 4.0 )
	? "Thursday "
	: ( ( dw == 5.0 )
	? "Friday "
	: ( ( dw == 6.0 )
	? "Saturday "
	: "Sunday " ) ) ) ) ) ) );
	 display( dd );
	 display( "." );
	 display( mm );
	 display( "." );
	 return
  yyyy;
	 }
double dd /* 41 */  = 21.0;
	 double mm /* 42 */  = 10.0;
	 double yyyy /* 43 */  = 2002.0;
	 int main() {
 display( birthday( day__of__week(  ) ) );
	 newline();
	 std::cin.get();
	 return
  0;
	 }

