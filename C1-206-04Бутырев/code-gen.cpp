/* $a04 */
#include "code-gen.h"
#include <sstream>
using namespace std;
void tCG::init(){
	declarations.clear();
	Authentication = "BDV";
//                  ^ 
// replace with your initials!!! 
}


//ok
int tCG::p01(){ // S -> PROG
	string header ="/*  " + Authentication +"   */\n";
	header += "#include \"mlisp.h\"\n";
	header += declarations;
	header += "//________________ \n";
	S1->obj = header + S1->obj;
	return 0;
}
int tCG::p02(){ //    PROG -> CALCS
	S1->obj = "int main() {\n " + S1->obj
		+ "std::cin.get();\n\t return\n  0;\n\t }\n";
	return 0;}
int tCG::p03(){ //    PROG -> DEFS
	S1->obj += "int main() {\n "
		"display( \"No calculations!\" );\n\t newline();\n\t "
		" std::cin.get();\n\t return\n  0;\n\t }\n";
	return 0;}
int tCG::p04(){ //    PROG -> DEFS CALCS
    S1->obj += "int main() {\n " + S2->obj
        + "std::cin.get();\n\t return\n  0;\n\t }\n";
	return 0;}






//ok
int tCG::p05(){ //       E -> $id
	S1->obj = decor( S1->name );
	return 0;}
int tCG::p06(){ //       E -> $int
    S1->obj = S1->name + ".0";
	return 0;}
int tCG::p07(){ //       E -> $dec
	S1->obj = S1->name;
	return 0;}



int tCG::p08(){ //       E -> AREX
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p09(){ //       E -> COND
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p10(){ //       E -> EASYLET
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p11(){ //       E -> CPROC
	return 0;}



//ok
int tCG::p12(){ // EASYLET -> HEASYL E )
	S1->obj += S2->obj;
	return 0;}
int tCG::p13(){ //  HEASYL -> ( let ( )
	return 0;}
int tCG::p14(){ //  HEASYL -> HEASYL INTER
	S1->obj += S2->obj + ",\n\t ";
	return 0;}



//ok
int tCG::p15(){ //    AREX -> HAREX E )
//  если будет только 1 элемент и оператор, то я попаду сюда
//	S1->obj += S2->obj;
	if( S1->count == 0 ) { // 1 элемент
		char type = S1->name[ 0 ];
		if( ( type == '+' ) || ( type == '-' ) ) {
			S1->obj = std::string( { type } ) + S2->obj;
		} else if( type == '*' ) {
			S1->obj = S2->obj;
		} else if( type == '/' ) {
			S1->obj = std::string( "1.0 / " ) + S2->obj;
		}
	} else if( S1->count == 1 ) { //2 элемента самое простое
		S1->obj += S2->obj;
	} else if( S1->count > 1 ){ // > 2 элементов
		char type = S1->name[ 0 ];
		if( ( type == '+' ) || ( type == '*' ) ) {
			S1->obj += S2->obj;
		} else if( ( type == '/' ) || ( type == '-' ) ) {
			S1->obj += S2->obj + " )";
		}
    }
	return 0;}
int tCG::p16(){ //   HAREX -> ( AROP
	S1->name = S2->name;
	S1->count = 0;
	return 0;}
int tCG::p17(){ //   HAREX -> HAREX E
	// однозначно > 1 аргумента
	// это преобразование "ест" по одной Е,
	// пока не останется только 1-а Е
	// но harex может не содержать Е
	char type = S1->name[ 0 ];
	if( ( type == '+' ) || ( type == '*' ) ) {
		S1->obj += S2->obj
			+ std::string( { ' ', type, ' ' } );
	} else if( type == '/' ) { //тут сложно
		if( S1->count == 0 ) { //first
			S1->obj = S2->obj + " / ";
		} else if ( S1->count == 1 ) {// будет > 2 аргументов
			S1->obj += "( " + S2->obj + " * ";
		} else {
			S1->obj += S2->obj + " * ";
		}
	}
	else if( type == '-' ) { //и тут сложно
		if( S1->count == 0 ) { //first
			S1->obj = S2->obj + " - ";
		} else if ( S1->count == 1 ) {
			S1->obj += "( " + S2->obj + " + ";
		} else {
			S1->obj += S2->obj + " + ";
		}
	}
	++( S1->count );
	return 0;}
int tCG::p18(){ //    AROP -> +
	S1->name = '+';
	return 0;}
int tCG::p19(){ //    AROP -> -
	S1->name = '-';
	return 0;}
int tCG::p20(){ //    AROP -> *
	S1->name = '*';
	return 0;}
int tCG::p21(){ //    AROP -> /
	S1->name = '/';
	return 0;}



//ok
int tCG::p22(){ //   CPROC -> HCPROC )
    S1->obj += " )";
	return 0;}
int tCG::p23(){ //  HCPROC -> ( $id
    S1->count = 0;
    S1->obj = decor( S2->name ) + "( ";
	return 0;}
int tCG::p24(){ //  HCPROC -> HCPROC E
    if( S1->count++ )
        S1->obj += ", ";
    S1->obj += S2->obj;
	return 0;}





//ok
//может не быть конечной ветви и нужно это отслеживать
//и там должно быть _infinity
//но мейби мой вариант такого не подразумевает
int tCG::p25(){ //    COND -> ( cond BRANCHES )
	S1->obj = S3->obj;
	return 0;}
int tCG::p26(){ //BRANCHES -> CLAUS
	S1->obj += "\n\t: _infinity";
	return 0;}
int tCG::p27(){ //BRANCHES -> CLAUS BRANCHES
	S1->obj += "\n\t: " + S2->obj;
	return 0;}
int tCG::p28(){ //   CLAUS -> ( BOOL E )
	S1->obj = S2->obj + "\n\t? " + S3->obj;
	return 0;}





//ok
int tCG::p29(){ //     STR -> $str
	S1->obj = S1->name;
	return 0;}
int tCG::p30(){ //     STR -> SIF
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p31(){ //     SIF -> ( if BOOL STR STR )
	S1->obj = S3->obj + "\n\t? " + S4->obj
		+ "\n\t: " + S5->obj;
	return 0;}


//ok
int tCG::p32(){ //    BOOL -> $bool
	if( S1->name == "#t" )
		S1->obj = "true";
	else
		S1->obj = "false";
	return 0;}
int tCG::p33(){ //    BOOL -> $idq
	S1->obj = decor( S1->name );
	return 0;}
int tCG::p34(){ //    BOOL -> REL
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p35(){ //    BOOL -> ( not BOOL )
	S1->obj = "!" + S3->obj;
	return 0;}
int tCG::p36(){ //    BOOL -> OR
	S1->obj = "( " + S1->obj + " )";
	return 0;}
int tCG::p37(){ //    BOOL -> CPRED
	return 0;}
int tCG::p38(){ //      OR -> ( or ORARGS )
	S1->obj = S3->obj;
	return 0;}
int tCG::p39(){ //  ORARGS -> BOOL ORARGS
	S1->obj = S1->obj + " || " + S2->obj;
	return 0;}
int tCG::p40(){ //  ORARGS -> BOOL
	return 0;}




//ok
int tCG::p41(){ //   CPRED -> ( $idq )
	S1->obj = decor( S2->name ) + "();\n\t ";
	return 0;}
int tCG::p42(){ //   CPRED -> ( $idq PDARGS )
	S1->obj = decor( S2->name ) + "( " + S3->obj + " )";
	return 0;}
int tCG::p43(){ //  PDARGS -> ARG
	return 0;}
int tCG::p44(){ //  PDARGS -> ARG PDARGS
	S1->obj = S1->obj + ", " + S2->obj;
	return 0;}
int tCG::p45(){ //     ARG -> E
	return 0;}
int tCG::p46(){ //     ARG -> BOOL
	return 0;}


//ok
int tCG::p47(){ //     REL -> ( = E E )
	S1->obj = S3->obj + " == " + S4->obj;
	return 0;}
int tCG::p48(){ //     REL -> ( > E E )
	S1->obj = S3->obj + " > " + S4->obj;
	return 0;}




int tCG::p49(){ // DISPSET -> ( display E )
	S1->obj = "display( " + S3->obj + " )";
	return 0;}
int tCG::p50(){ // DISPSET -> ( display BOOL )
	S1->obj = "display( " + S3->obj + " )";
	return 0;}
int tCG::p51(){ // DISPSET -> ( display STR )
	S1->obj = "display( " + S3->obj + " )";
	return 0;}
int tCG::p52(){ // DISPSET -> ( newline )
	S1->obj = "newline()";
	return 0;}
int tCG::p53(){ // DISPSET -> SET
	return 0;}



int tCG::p54(){ //   INTER -> DISPSET
	return 0;}
int tCG::p55(){ //   INTER -> E
	return 0;}



int tCG::p56(){ //   CALCS -> CALC
	return 0;}
int tCG::p57(){ //   CALCS -> CALCS CALC
	S1->obj += S2->obj;
	return 0;}
int tCG::p58(){ //    CALC -> E
	S1->obj = "display( " + S1->obj + " );\n\t newline();\n\t ";
	return 0;}
int tCG::p59(){ //    CALC -> BOOL
	S1->obj = "display( " + S1->obj + " );\n\t newline();\n\t ";
	return 0;}
int tCG::p60(){ //    CALC -> STR
	S1->obj = "display( " + S1->obj + " );\n\t newline();\n\t ";
	return 0;}
int tCG::p61(){ //    CALC -> DISPSET
	S1->obj += ";\n\t ";
	return 0;}



//ok
int tCG::p62(){ //    DEFS -> DEF
	return 0;}
int tCG::p63(){ //    DEFS -> DEFS DEF
    S1->obj += S2->obj;
	return 0;}
int tCG::p64(){ //     DEF -> PRED
	return 0;}
int tCG::p65(){ //     DEF -> VAR
	std::stringstream str( S1->obj );
	std::string vardecl;
	std::string varini;
	std::getline( str, vardecl, '\n' );
	std::getline( str, varini, '\n' );
	declarations += "extern " + vardecl
		+ " /* " + S1->line + " */ ;\n\t ";
	S1->obj = vardecl + " /* " + S1->line + " */ "
		+ " = " + varini + ";\n\t ";
	return 0;}
int tCG::p66(){ //     DEF -> PROC
	return 0;}
int tCG::p67(){ //    PRED -> HPRED BOOL )
	S1->obj += S2->obj + ";\n\t }\n";
	return 0;}
int tCG::p68(){ //   HPRED -> PDPAR )
	S1->obj += " )";
	declarations += S1->obj + ";\n\t ";
	S1->obj += " {\n return\n  ";
	return 0;}
int tCG::p69(){ //   PDPAR -> ( define ( $idq
	S1->obj =  "bool " + decor( S4->name )
		+ " /* " + S4->line + " */ ( ";
	S1->count = 0;
	return 0;}
int tCG::p70(){ //   PDPAR -> PDPAR $idq
	if( S1->count )
		S1->obj += S1->count % 2 ? ", " : "\n\t , ";
	S1->obj += "bool " + decor( S2->name );
	++( S1->count );
	return 0;}
int tCG::p71(){ //   PDPAR -> PDPAR $id
	if( S1->count )
		S1->obj += S1->count % 2 ? ", " : "\n\t , ";
	S1->obj += "double " + decor( S2->name );
	++( S1->count );
	return 0;}
int tCG::p72(){ //     SET -> ( set! $id E )
    S1->obj += decor( S3->name ) + " = " + S4->obj;
	return 0;}





int tCG::p73(){ //     VAR -> VARDCL VARINI )
	S1->obj += "\n" + S2->obj + '\n';
	//S1->line
	return 0;}
int tCG::p74(){ //  VARDCL -> ( define $id
	S1->obj = "double " + decor( S3->name );
	return 0;}
int tCG::p75(){ //  VARINI -> $int
	S1->obj = S1->name + ".0";
	return 0;}
int tCG::p76(){ //  VARINI -> $dec
	S1->obj = S1->name;
	return 0;}



int tCG::p77(){ //    PROC -> HPROC PCBODY )
	S1->obj += S2->obj + "}\n";
	return 0;}
int tCG::p78(){ //   HPROC -> PCPAR )
	S1->obj += " )";
	declarations += S1->obj + ";\n\t ";
	S1->obj += " {\n ";
	return 0;}
int tCG::p79(){ //  PCBODY -> E
	S1->obj = "return\n  " + S1->obj + ";\n\t ";
	return 0;}
int tCG::p80(){ //  PCBODY -> INTER PCBODY
	S1->obj += ";\n\t " + S2->obj;
	return 0;}
int tCG::p81(){ //  PCBODY -> VAR PCBODY
	// нужно разбить по \n и добавить ( )
	std::stringstream str( S1->obj );
	std::string vardecl;
	std::string varini;
	std::getline( str, vardecl, '\n' );
	std::getline( str, varini, '\n' );
 	S1->obj = vardecl + "( " + varini + " );\n\t " + S2->obj;
	return 0;}
int tCG::p82(){ //   PCPAR -> ( define ( $id
	S1->obj =  "double " + decor( S4->name )
		+ " /* " + S4->line + " */ ( ";
	S1->count = 0;
	return 0;}
int tCG::p83(){ //   PCPAR -> PCPAR $id
	if( S1->count )
		S1->obj += S1->count % 2 ? ", " : "\n\t , ";
	S1->obj += "double " + decor( S2->name );
	++( S1->count );
	return 0;}
//_____________________
int tCG::p84(){return 0;} int tCG::p85(){return 0;} 
int tCG::p86(){return 0;} int tCG::p87(){return 0;} 
int tCG::p88(){return 0;} int tCG::p89(){return 0;} 
int tCG::p90(){return 0;} int tCG::p91(){return 0;} 
int tCG::p92(){return 0;} int tCG::p93(){return 0;} 
int tCG::p94(){return 0;} int tCG::p95(){return 0;} 
int tCG::p96(){return 0;} int tCG::p97(){return 0;} 
int tCG::p98(){return 0;} int tCG::p99(){return 0;} 
int tCG::p100(){return 0;} int tCG::p101(){return 0;} 
int tCG::p102(){return 0;} int tCG::p103(){return 0;} 
int tCG::p104(){return 0;} int tCG::p105(){return 0;} 
int tCG::p106(){return 0;} int tCG::p107(){return 0;} 
int tCG::p108(){return 0;} int tCG::p109(){return 0;} 
int tCG::p110(){return 0;} 

