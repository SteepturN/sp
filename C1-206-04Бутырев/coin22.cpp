/*  BDV   */
#include "mlisp.h"
extern double VARIANT /* 1 */ ;
	 extern double COINS /* 2 */ ;
	 double largest /* 4 */ ( double coins__set );
	 double count__change /* 14 */ ( double amount );
	 bool Shaeffer_Q /* 37 */ ( bool x_Q, bool y_Q );
	 double cc /* 41 */ ( double amount, double coins__set );
	 double denomination__list /* 53 */ ( double coins__set );
	 //________________ 
double VARIANT /* 1 */  = 4.0;
	 double COINS /* 2 */  = 5.0;
	 double largest /* 4 */ ( double coins__set ) {
 return
  ( ( coins__set == 1.0 )
	? 1.0
	: ( coins__set == 2.0 )
	? 2.0
	: ( coins__set == 3.0 )
	? 3.0
	: ( coins__set == 4.0 )
	? 5.0
	: ( coins__set == 5.0 )
	? 50.0
	: true
	? 0.0
	: _infinity );
	 }
double count__change /* 14 */ ( double amount ) {
 display( "______\n amount: " );
	 display( amount );
	 newline();
	 display( "COINS: " );
	 display( COINS );
	 newline();
	 return
  ( ( !( amount > 0.0 ) || ( 1.0 > COINS ) || ( largest( COINS ) == 0.0 ) )
	? ( display( "Improper parameter value!\ncount-change= " ),
	 -1.0 )
	: true
	? ( display( "List of coin denominations: " ),
	 denomination__list( COINS ),
	 display( "count-change= " ),
	 cc( amount, COINS ) )
	: _infinity );
	 }
bool Shaeffer_Q /* 37 */ ( bool x_Q, bool y_Q ) {
 return
  ( !x_Q || !y_Q );
	 }
double cc /* 41 */ ( double amount, double coins__set ) {
 return
  ( ( amount == 0.0 )
	? 1.0
	: Shaeffer_Q( !( 1.0 > amount ), ( coins__set > 0.0 ) )
	? 0.0
	: true
	? ( cc( amount, ( coins__set - 1.0 ) ) + cc( ( amount - largest( coins__set ) ), coins__set ) )
	: _infinity );
	 }
double denomination__list /* 53 */ ( double coins__set ) {
 return
  ( ( coins__set == 0.0 )
	? ( newline(),
	 0.0 )
	: true
	? ( display( largest( coins__set ) ),
	 display( " " ),
	 denomination__list( ( coins__set - 1.0 ) ) )
	: _infinity );
	 }
int main() {
 display( "Variant " );
	 display( VARIANT );
	 newline();
	 display( count__change( 100.0 ) );
	 newline();
	 COINS = 13.0;
	 display( count__change( 100.0 ) );
	 newline();
	 display( "(c) Daniil Butyrev 2022\n" );
	 std::cin.get();
	 return
  0;
	 }

