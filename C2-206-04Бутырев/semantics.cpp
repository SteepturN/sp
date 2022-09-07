//(c) Butyrev Daniil 2022
/* $a04 */
#include "semantics.h"
#include <iostream>
using namespace std;
enum Scope {
	LOCAL_SC = 1,
	GLOBAL_SC = 0,
};
enum explicit_enum {
	VAR_TYPES = 0,
	VAR_ARITY = 0,
	PROC_TYPES = 0,
};

void tSM::init(){
	globals.clear();
	locals.clear();
	scope = 0;

	globals[ "e" ] = tgName( VAR | DEFINED | BUILT, "", VAR_ARITY, VAR_TYPES );
	globals[ "pi" ] = tgName( VAR | DEFINED | BUILT, "", VAR_ARITY, VAR_TYPES );

	globals[ "abs" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "atan" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "cos" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "exp" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "expt" ] = tgName( PROC | DEFINED | BUILT, "", 2, 0 );
	globals[ "log" ] = tgName( PROC | DEFINED | BUILT, "", 2, 0 );
	globals[ "quotient" ] = tgName( PROC | DEFINED | BUILT, "", 2, 0 );
	globals[ "reminder" ] = tgName( PROC | DEFINED | BUILT, "", 2, 0 );
	globals[ "sin" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "sqrt" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	globals[ "tan" ] = tgName( PROC | DEFINED | BUILT, "", 1, 0 );
	return;}
int tSM::p01(){ //       S -> PROG
	bool error = false;
	for( auto& [ name, global_unit ] : globals ){
		if( global_unit.test( BUILT ) ) continue;
		else if( global_unit.test( USED ) && !global_unit.test( DEFINED ) ) {
			if( global_unit.test( VAR ) )
				ferror_message +=
					"Error[01-1] in line "+ global_unit.line + ": the \'" + name
					+ "\' variable is used, but not defined\n";
			//переменная _ использована, но не определена
			//the _ variable is used, but not defined
			else
				ferror_message +=
					"Error[01-2] in line "+ global_unit.line + ": the \'" + name
					+ "\' function is used, but not defined\n";
			//функция _ использована, но не определена
			//the _ function is used, but not defined
			error = true;
		} else if( global_unit.test( DEFINED ) && ( !global_unit.test( USED ) ) ) {
			if( global_unit.test( VAR ) )
				ferror_message +=
					"Warning[01-3] in line "+ global_unit.line + ": the \'" + name
					+ "\' variable is defined, but not used\n";
			//переменная _ определена, но не использована
			//the _ variable is defined, but not used
			else
				ferror_message +=
					"Warning[01-4] in line "+ global_unit.line + ": the \'" + name
					+ "\' function is defined, but not used\n";
			//функция _ определена, но не использована
			//the _ function is defined, but not used

		}
	}//for...
	if( error ) return 1;
	return 0;}
int tSM::p02(){ //    PROG -> CALCS
	return 0;}
int tSM::p03(){ //    PROG -> DEFS
	return 0;}
int tSM::p04(){ //    PROG -> DEFS CALCS
	return 0;}

int tSM::p05(){ //       E -> $id
	std::string var_name = S1->name;
	if( !( locals.count( var_name ) || globals.count( var_name ) ) ) {
		globals[ var_name ] = tgName( VAR | USED, S1->line, VAR_ARITY, VAR_TYPES );
		return 0;
	} else if( ( scope == LOCAL_SC ) && locals.count( var_name ) ) {
		return 0;
	} else if( globals[ var_name ].test( BUILT | PROC ) ){
		ferror_message +=
			"Error[05-1] in line " + S1->line + ": using the built-in procedure '"
			+ var_name +
			"' as a variable\n";
		//использование встроенной процедуры _ как переменной
		//using the built-in procedure _ as a variable
		return 1;
	} else if( globals[ var_name ].test( PROC ) ) {
		ferror_message +=
			"Error[05-2] in line " + S1->line + ": using the \'"
			+ var_name + "\' procedure as a variable.\nThe first mention of this name was on the "
			+ globals[ var_name ].line + " line\n";
		//использование процедуры _ как переменной. Первое упоминание данного имени было на _ строке
		//using the _ procedure as a variable. The first mention of this name was on the _ line
		return 1;
	} else {
		globals[ var_name ].set( USED );
	}
	return 0;}


int tSM::p06(){ //       E -> $int
	return 0;}
int tSM::p07(){ //       E -> $dec
	return 0;}
int tSM::p08(){ //       E -> AREX
	return 0;}
int tSM::p09(){ //       E -> COND
	return 0;}
int tSM::p10(){ //       E -> EASYLET
	return 0;}
int tSM::p11(){ //       E -> CPROC
	return 0;}



int tSM::p12(){ // EASYLET -> HEASYL E )
	return 0;}
int tSM::p13(){ //  HEASYL -> ( let ( )
	return 0;}
int tSM::p14(){ //  HEASYL -> HEASYL INTER
	return 0;}
int tSM::p15(){ //    AREX -> HAREX E )
	return 0;}
int tSM::p16(){ //   HAREX -> ( AROP
	return 0;}
int tSM::p17(){ //   HAREX -> HAREX E
	return 0;}
int tSM::p18(){ //    AROP -> +
	return 0;}
int tSM::p19(){ //    AROP -> -
	return 0;}
int tSM::p20(){ //    AROP -> *
	return 0;}
int tSM::p21(){ //    AROP -> /
	return 0;}




int tSM::p22(){ //   CPROC -> HCPROC )
	std::string func_name = S1->name;
	if( globals[ func_name ].empty() ) {
		//ok - create one
		globals[ func_name ] = tgName( PROC | USED, S1->line, S1->count, PROC_TYPES );
	} else if( globals[ func_name ].test( BUILT ) &&
			   ( globals[ func_name ].arity != S1->count ) ) {
		//error
		ferror_message +=
			"Error[22-1] in line " + S1->line
			+ ": using the built-in \'" + func_name
			+ "\' procedure\nwith the wrong number of arguments: "
			+ std::to_string( S1->count ) + ", you need to use: "
			+ std::to_string( globals[ func_name ].arity ) + " argument(s)\n";
		// использование встроенной процедуры _ с неправильным
		// количеством аргументов _, нужно использовать _ аргументов
		// using the built-in _ procedure with the wrong
		// number of arguments _, you need to use _ arguments
		return 1;
	} else if( globals[ func_name ].arity != S1->count ) {
		//error
		ferror_message +=
			"Error[22-2] in line " + S1->line
			+ ": using the procedure name \'" + func_name + "\'\nwith the number of arguments: "
			+ std::to_string( S1->count )
			+ "\nthat does not match the previous mention of this procedure: "
			+ std::to_string( globals[ func_name ].arity )
			+ ".\nThe first mention of this name was on the "
			+ globals[ func_name ].line + " line.\n";
		// использование имени процедуры _ с количеством аргументов _,
		// не совпадающим с предыдущим упоминанием этой процедуры _.
		// Первое упоминание данного имени было на _ строке
		// using the procedure name _ with the number of arguments _
		// that does not match the previous mention of this procedure:_
		// The first mention of this name was on the _ line
		return 1;
	} else {
		globals[ S1->name ].set( USED );
	}
	return 0;}
int tSM::p23(){ //  HCPROC -> ( $id
	S1->count = 0;
	std::string func_name = S1->name = S2->name;
	if( ( scope == LOCAL_SC ) && locals.count( func_name ) ) {
			ferror_message += "Error[23-1] in line " + S2->line
				+ ": instead of the procedure name,\nthe name of the local variable is used: \'"
				+ func_name + "\'\n";
			// вместо имени процедуры используется используется имя локальной переменной: _
			// instead of the procedure name, the name of the local variable is used: _
			return 1;
	} else if( globals[ func_name ].test( VAR | BUILT ) ) {
		ferror_message +=
			"Error[23-2] in line " + S1->line
			+ ": using the name of the built-in variable \'"
			+ func_name + "\' to call a function\n";
		// использование имени встроенной переменной _ для вызова процедуры
		// using the name of the built-in variable _ to call a function
		return 1;
	} else if( globals[ func_name ].test( VAR ) ) {
		ferror_message +=
			"Error[23-3] in line " + S1->line
			+ ": using the variable name \'"
			+ func_name + "\' to call a function.\nThe first mention of this name was on the "
			+ globals[ func_name ].line + " line\n";
		// использование имени переменной _ для вызова процедуры.
		// Первое упоминание данного имени было на _ строке
		// using the variable name _ to call a function.
		// The first mention of this name was on the _ line
		return 1;
	}
	return 0;}
int tSM::p24(){ //  HCPROC -> HCPROC E
	++S1->count;
	return 0;}




int tSM::p25(){ //    COND -> ( cond BRANCHES )
	return 0;}
int tSM::p26(){ //BRANCHES -> CLAUS
	return 0;}
int tSM::p27(){ //BRANCHES -> CLAUS BRANCHES
	return 0;}
int tSM::p28(){ //   CLAUS -> ( BOOL E )
	return 0;}
int tSM::p29(){ //     STR -> $str
	return 0;}
int tSM::p30(){ //     STR -> SIF
	return 0;}
int tSM::p31(){ //     SIF -> ( if BOOL STR STR )
	return 0;}
int tSM::p32(){ //    BOOL -> $bool
	return 0;}



int tSM::p33(){ //    BOOL -> $idq
	if( scope != LOCAL_SC ) {
		ferror_message += std::string( "Error[33-1] you cannot use a variable of type bool \'" )
			+ S1->name + "\'\noutside of the predicate definition\n";
		// нельзя использовать переменную типа bool _ вне определения предиката
		// you cannot use a variable of type bool _ outside of the predicate definition
		return 1;
	} else if( !locals.count( S1->name ) ) {
		//error
		ferror_message += "Error[33-2] in line " + S1->line
			+ ": the variable \'" + S1->name
			+ "\' is not a predicate argument\n";
		// переменная _ не является аргументом предиката
		// the variable _ is not a predicate argument
		return 1;
	}
	return 0;}





int tSM::p34(){ //    BOOL -> REL
	return 0;}
int tSM::p35(){ //    BOOL -> ( not BOOL )
	return 0;}
int tSM::p36(){ //    BOOL -> OR
	return 0;}
int tSM::p37(){ //    BOOL -> CPRED
	return 0;}
int tSM::p38(){ //      OR -> ( or ORARGS )
	return 0;}
int tSM::p39(){ //  ORARGS -> BOOL ORARGS
	return 0;}
int tSM::p40(){ //  ORARGS -> BOOL
	return 0;}





int tSM::p41(){ //   CPRED -> ( $idq )
	std::string func_name = S2->name;
	if( ( scope == LOCAL_SC ) && locals.count( func_name ) ) {
			ferror_message += "Error[41-1] in line " + S2->line
				+ ": the name of the local variable is used\ninstead of the predicate name: \'"
				+ func_name + "\'\n";
			// вместо имени предиката используется используется имя локальной переменной: _
			// the name of the local variable is used instead of the predicate name: _
			return 1;
	} else if( globals[ func_name ].empty() ) {
		globals[ func_name ] = tgName( PROC | USED, S2->line, 0, 0 );
	} else if( globals[ func_name ].arity != 0 ) {
		ferror_message +=
			"Error[41-2] in line "+ S2->line +": when calling the predicate \'"
			+ func_name + "\',\nthe number of arguments: "
			+ '0' + "does not match the number of arguments\nwhen declaring it: "
			+ std::to_string( globals[ func_name ].arity ) + ".\n"
			+ "The first mention of this predicate was on the "
			+ globals[ func_name ].line + " line\n";
		// при вызове предиката _ количество аргументов _ не совпадает с
		// количеством аргументов при его объявлении _
		// Первое упоминание данного предиката было на _ строке
		// when calling the predicate _, the number of arguments _ does not match
		// the number of arguments when declaring it _
		// The first mention of this predicate was on the _ line
		return 1;
	} else {
		globals[ func_name ].set( USED );
	}
	return 0;}
int tSM::p42(){ //   CPRED -> ( $idq PDARGS )
	std::string func_name = S2->name;
	if( ( scope == LOCAL_SC ) && locals.count( func_name ) ) {
			ferror_message += "Error[42-1] in line " + S2->line
				+ ": the name of the local variable is used\ninstead of the predicate name: \'"
				+ func_name + "\'\n";
			// вместо имени предиката используется используется имя локальной переменной: _
			// the name of the local variable is used instead of the predicate name: _
			return 1;
	} else if( globals[ func_name ].empty() ) {
		globals[ func_name ] = tgName( PROC | USED, S2->line, S3->count, S3->types );
	} else if( globals[ func_name ].arity != S3->count ) {
		ferror_message +=
			"Error[42-2] in line "+ S2->line +": when calling the predicate \'"
			+ func_name + "\',\nthe number of arguments "
			+ std::to_string( S3->count ) + " does not match the number of arguments\nwhen declaring it "
			+ std::to_string( globals[ func_name ].arity ) + ".\n"
			+ "The first mention of this predicate was on the "
			+ globals[ func_name ].line + " line\n";
		// при вызове предиката _ количество аргументов _ не совпадает с
		// количеством аргументов при его объявлении _
		// Первое упоминание данного предиката было на _ строке
		// when calling the predicate _, the number of arguments _ does not match
		// the number of arguments when declaring it _
		// The first mention of this predicate was on the _ line
		return 1;
	} else if( globals[ func_name ].types != S3->types ) {
		//error
		std::string cur_types = "", prev_types = "";
		for( int i = 1; i <= S3->count; ++i ) {
			cur_types += ( S3->types & ( 1u << ( i - 1 ) ) ) == 0 ?
				"numeric_arg" : "boolean_arg";
			prev_types += ( globals[ func_name ].types & ( 1u << ( i - 1 ) ) ) == 0 ?
				"numeric_arg" : "boolean_arg";
			if( i != S3->count ) {
				cur_types += ", ";
				prev_types += ", ";
			}
			if( i % 6 == 0 ) {
				cur_types += '\n';
				prev_types += '\n';
			}
		}
		ferror_message+=
			"Error[42-3] in line "+ S1->line +": when calling the predicate \'"
			+ func_name +
			"\' the types of arguments:\n" + cur_types + "\ndo not match "
			+ "the types of arguments when declaring it:\n" + prev_types
			+ "\nThe first mention of this predicate was on the "
			+ globals[ func_name ].line + " line\n";
		// при вызове предиката _ типы аргументов _ не совпадают с
		// типами аргументов при его объявлении _
		// Первое упоминание данного предиката было на _ строке
		// when calling the predicate _, the types of arguments _ do not match the
		// types of arguments when declaring it _
		// The first mention of this predicate was on the _ line
		return 1;
	} else {
		globals[ func_name ].set( USED );
	}
	return 0;}
int tSM::p43(){ //  PDARGS -> ARG
	S1->count = 1;
	return 0;}
int tSM::p44(){ //  PDARGS -> ARG PDARGS
	S1->count = S2->count + 1;
	if( S1->count > 32 ) {
		ferror_message += std::string( "Error[44-1] in line " )
			+ S1->line
		+ " when calling the predicate, the maximum number of arguments\n"
		+ "that the analyzer model can correctly process was exceeded,\n"
		+ "which is 32, or rather 8*sizeof(int).\n";
		// при вызове предиката _ максимальное количество аргументов,
		// которое может корректно обработать модель анализатора,
		// равное 32, а точнее 8*sizeof(int).
		// when calling the predicate, the maximum number of arguments
		// that the analyzer model can correctly process was exceeded,
		// which is 32, or rather 8*sizeof(int).
		return 1;
	}
	S1->types |= ( S2->types << 1u );
	return 0;}
int tSM::p45(){ //     ARG -> E
	S1->types = 0;
	return 0;}
int tSM::p46(){ //     ARG -> BOOL
	S1->types = 1;
	return 0;}






int tSM::p47(){ //     REL -> ( = E E )
	return 0;}
int tSM::p48(){ //     REL -> ( > E E )
	return 0;}
int tSM::p49(){ // DISPSET -> ( display E )
	return 0;}
int tSM::p50(){ // DISPSET -> ( display BOOL )
	return 0;}
int tSM::p51(){ // DISPSET -> ( display STR )
	return 0;}
int tSM::p52(){ // DISPSET -> ( newline )
	return 0;}
int tSM::p53(){ // DISPSET -> SET
	return 0;}
int tSM::p54(){ //   INTER -> DISPSET
	return 0;}
int tSM::p55(){ //   INTER -> E
	return 0;}
int tSM::p56(){ //   CALCS -> CALC
	return 0;}
int tSM::p57(){ //   CALCS -> CALCS CALC
	return 0;}
int tSM::p58(){ //    CALC -> E
	return 0;}
int tSM::p59(){ //    CALC -> BOOL
	return 0;}
int tSM::p60(){ //    CALC -> STR
	return 0;}
int tSM::p61(){ //    CALC -> DISPSET
	return 0;}
int tSM::p62(){ //    DEFS -> DEF
	return 0;}
int tSM::p63(){ //    DEFS -> DEFS DEF
	return 0;}




int tSM::p64(){ //     DEF -> PRED
	locals.clear();
	scope = GLOBAL_SC;
	return 0;}
int tSM::p65(){ //     DEF -> VAR
	return 0;}
int tSM::p66(){ //     DEF -> PROC
	locals.clear();
	scope = GLOBAL_SC;
	return 0;}




int tSM::p67(){ //    PRED -> HPRED BOOL )
	scope = GLOBAL_SC;
	locals.clear();
	return 0;}
int tSM::p68(){ //   HPRED -> PDPAR )
	std::string pred_name = S1->name;
	if( globals[ pred_name ].empty() ) {
		globals[ pred_name ] = tgName( PROC | DEFINED, S1->line, S1->count, S1->types );
	} else if( globals[ pred_name ].test( USED ) ) {
		globals[ pred_name ].set( DEFINED );
		if( globals[ pred_name ].arity != S1->count ) {
			ferror_message +=
				"Error[68-1] in line " + S2->line
				+ ": the number of arguments\nof the predicate being defined \'"
				+ pred_name + "\': " + std::to_string( S1->count )
				+ "\ndoes not match its previous declaration: "
				+ std::to_string( globals[ pred_name ].arity )
				+ ".\nThe first declaration of the predicate was on the line "
				+ globals[ pred_name ].line + '\n';
			// количество аргументов определяемого предиката _: _ не совпадает с его предыдущим
			// объявлением: _. Первое объявление предиката было на строке _
			// the number of arguments of the predicate being defined _: _ does not match its previous
			// declaration: _. The first declaration of the predicate was on the line _
			return 1;
		} else if( globals[ pred_name ].types != S1->types ) {
			std::string cur_types = "", prev_types = "";
			for( int i = 1; i <= S1->count; ++i ) {
				cur_types += ( S1->types & ( 1u << ( i - 1 ) ) ) == 0 ?
					"numeric_arg" : "boolean_arg";
				prev_types += ( globals[ pred_name ].types & ( 1u << ( i - 1 ) ) ) == 0 ?
					"numeric_arg" : "boolean_arg";
				if( i != S1->count ) {
					cur_types += ", ";
					prev_types += ", ";
				}
				if( i % 6 == 0 ) {
					cur_types += '\n';
					prev_types += '\n';
				}
			}
			ferror_message +=
				"Error[68-2] in line "+ S1->line +": when defining the predicate \'"
				+ pred_name +
				"\'\nthe types of arguments:\n" + cur_types + "\ndo not match "
				+ "the types of arguments when declaring it:\n" + prev_types
				+ "\nThe first mention of this predicate was on the "
				+ globals[ pred_name ].line + " line\n";
			// при определении предиката _ типы аргументов _ не совпадают с
			// типами аргументов при его объявлении _
			// Первое упоминание данного предиката было на _ строке
			// when defining the predicate _, the types of arguments _ do not match the
			// types of arguments when declaring it _
			// The first mention of this predicate was on the _ line
			return 1;
		}
	}
	return 0;}
int tSM::p69(){ //   PDPAR -> ( define ( $idq
	std::string pred_name = S4->name;
	locals.clear();
	S1->name = S4->name;
	S1->count = 0;
	S1->types = 0;
	scope = LOCAL_SC;
	if( globals[ pred_name ].test( DEFINED ) ) {
		ferror_message +=
			"Error[69-1] in line " + S2->line
			+ ": the name of the predicate being defined \'"
			+ pred_name + "\'\nhas already been used previously to define a function"
			+ ".\nThe first mention of this name was on the "
			+ globals[ pred_name ].line + " line.\n";
			// имя определяемого предиката _ уже было использовано ранее для определения
			// переменной/функции.
			// Первое упоминание данного имени было на _ строке.
			// the name of the predicate being defined _ has already been used
			// previously to define a variable/function.
			// The first mention of this name was on the _ line.
		return 1;
	}
	return 0;}
int tSM::p70(){ //   PDPAR -> PDPAR $idq
    if( locals.count( S2->name ) ){
		ferror_message +=
			"Error[70-1] in line " + S2->line
			+ ": when defining the predicate \'"
			+ S1->name
			+ "\',\nthe name of the argument is duplicated: \'"
			+ S2->name + "\'\n";
		// при определении предиката _ дублируется имя аргумента _
		// when defining the predicate _, the name of the argument is duplicated _
		return 1;
    }
    if( S2->name == S1->name ){
		ferror_message +=
			"Warning[70-2] in line "+ S2->line +": when defining the predicate \'"
			+ S1->name +
			"\'\none of the arguments duplicates the name of the predicate\n";
		// при определении предиката _ один из аргументов
		// дублирует имя предиката
		// when defining the predicate _, one of the arguments
		// duplicates the name of the predicate
    }
    locals.insert( S2->name );
	S1->types |= 1u << S1->count;
	++S1->count;
	if( S1->count > 32 ) {
		ferror_message += std::string( "Error[70-3] in line " )
			+ S1->line
			+ " when defining the predicate \'"
			+ S1->name + "\', the maximum number of arguments\n"
			+ "that the analyzer model can correctly process was exceeded,\n"
			+ "which is 32, or rather 8*sizeof(int).\n";
		// при определении предиката _ было превышено максимальное количество аргументов,
		// которое может корректно обработать модель анализатора,
		// равное 32, а точнее 8*sizeof(int).
		// when defining the predicate _, the maximum number of arguments
		// that the analyzer model can correctly process was exceeded,
		// which is 32, or rather 8*sizeof(int).
		return 1;
	}
	return 0;}
int tSM::p71(){ //   PDPAR -> PDPAR $id
    if( locals.count( S2->name ) ){
		ferror_message +=
			"Error[71-1] in line " + S2->line
			+ ": when defining the predicate \'"
			+ S1->name
			+ "\',\nthe name of the argument is duplicated: \'"
			+ S2->name + "\'\n";
		// при определении предиката _ дублируется имя аргумента _
		// when defining the predicate _, the name of the argument is duplicated _
		return 1;
    }
    locals.insert( S2->name );
	++S1->count;
	if( S1->count > 32 ) {
		ferror_message += std::string( "Error[71-2] in line " )
			+ S1->line
			+ " when defining the predicate \'"
			+ S1->name + "\',\nthe maximum number of arguments\n"
			+ "that the analyzer model can correctly process was exceeded,\n"
			+ "which is 32, or rather 8*sizeof(int).\n";
		// при определении предиката _ было превышено максимальное количество аргументов,
		// которое может корректно обработать модель анализатора,
		// равное 32, а точнее 8*sizeof(int).
		// when defining the predicate _, the maximum number of arguments
		// that the analyzer model can correctly process was exceeded,
		// which is 32, or rather 8*sizeof(int).
		return 1;
	}
	return 0;}






int tSM::p72(){ //     SET -> ( set! $id E )
	std::string var_name = S3->name;
	if( !( locals.count( var_name ) || globals.count( var_name ) ) ) {
		globals[ var_name ] = tgName( VAR | USED, S3->line, VAR_ARITY, VAR_TYPES );
		return 0;
	} else if( ( scope == LOCAL_SC ) && locals.count( var_name ) ) {
		return 0;
	} else if( globals[ var_name ].test( BUILT ) ){
		if( globals[ var_name ].test( PROC ) ) {
			ferror_message +=
				"Error[72-1] in line "+ S1->line
				+ ": assigning a value to a built-in procedure \'"
				+ var_name + "\'\n";
			// присваивание встроенной процедуре _ значения
			// assigning a value to the built-in procedure _
		} else { //VAR
			ferror_message +=
				"Error[72-2] in line "+ S2->line +": assigning a value to the built-in constant \'"
				+ var_name + "\'\n";
			// присваивание встроенной константе _ значения
			// assigning a value to the built-in constant _
		}
		return 1;
	} else if( globals[ var_name ].test( PROC ) ) {
		ferror_message +=
			"Error[72-3] in line "+ S1->line
			+ ": using the procedure name \'" + var_name
			+ "\' to assign a value to it.\n"
			+ "The first mention of this name was on the "
			+ globals[ var_name ].line + " line.\n";
		// использование имени процедуры _ для присваивания ей значения
		// Первое упоминание данного имени было на _ строке.
		// using the procedure name _ to assign a value to it
		// The first mention of this name was on the _ line.
		return 1;
	} else {
		globals[ var_name ].set( USED );
	}
	return 0;}






int tSM::p73(){ //     VAR -> VARDCL VARINI )
	return 0;}
int tSM::p74(){ //  VARDCL -> ( define $id
	std::string var_name = S3->name;
	if( scope == LOCAL_SC ) {
		if( locals.count( var_name ) ) {
			ferror_message +=
				"Error[74-1] in line " + S2->line
				+ ": in the definition of the procedure,\n"
				+ "there is a repeated definition of the variable \'"
				+ var_name + "\'\n";
			// в определении процедуры присутствует повторное определение переменной _
			// in the definition of the procedure, there is a repeated definition of the variable _
			return 1;
		} else {
			locals.insert( var_name );
		}
	} else { //GLOBAL_SC
		if( globals[ var_name ].empty() ) {
			globals[ var_name ] = tgName( VAR | DEFINED, S3->line, VAR_ARITY, VAR_TYPES );
		} else if( globals[ var_name ].test( BUILT ) ) {
			std::string other_unit;
			ferror_message +=
				"Error[74-2] in line "+ S2->line +": the name of the defined variable \'"
				+ var_name + "\'\nis the same as the name of the built-in "
				+ ( globals[ var_name ].test( VAR ) ? "variable" : "function" )
				+ '\n';
			// имя определяемой переменной _ совпадает с именем встроенной функции/переменной
			// the name of the defined variable _ is the same as the name of the built-in function/variable
			return 1;
		} else if( globals[ var_name ].test( PROC ) ) {
			std::string add_info;
			ferror_message +=
				"Error[74-3] in line " +
				S2->line + ": the name of the variable being defined \'"
				+ var_name + "\'\nhas already been used when declaring the procedure.\n"
				+ "The first mention of this name was on the " + globals[ var_name ].line
				+ " line\n";
			// имя определяемой переменной _ уже было использовано при объявлении процедуры.
			// Первое упоминание данного имени было на _ строке.
			// the name of the variable being defined _ has already been used when declaring the procedure.
			// The first mention of this name was on the _ line.
			return 1;
		} else if( globals[ var_name ].test( /*VAR*/ DEFINED ) ) {
			ferror_message +=
				"Error[74-4] in line " + S2->line
				+ ": the name of the variable being defined \'"
				+ var_name + "\'\nhas already been used when defining another variable.\n"
				+ "The first mention of this name was on the "
				+ globals[ var_name ].line + " line\n";
			// имя определяемой переменной _ уже было использовано при определении другой переменной.
			// Первое упоминание данного имени было на _ строке.
			// the name of the variable being defined _ has already been used when defining another variable.
			// The first mention of this name was on the _ line.
			return 1;
		} else { //used + var
			globals[ var_name ].set( DEFINED );
		}
	}
	return 0;}
int tSM::p75(){ //  VARINI -> $int
	return 0;}
int tSM::p76(){ //  VARINI -> $dec
	return 0;}


int tSM::p77(){ //    PROC -> HPROC PCBODY )
	scope = GLOBAL_SC;
	return 0;}
int tSM::p78(){ //   HPROC -> PCPAR )
	std::string proc_name = S1->name;
	if( globals[ proc_name ].empty() ) {
		globals[ proc_name ] = tgName( PROC | DEFINED, S1->line, S1->count, PROC_TYPES );
	} else if( globals[ proc_name ].test( USED ) ) {
		globals[ proc_name ].set( DEFINED );
		if( globals[ proc_name ].arity != S1->count ) {
			ferror_message +=
				"Error[78-1] in line " + S2->line
				+ ": the number of arguments\nof the procedure being defined \'"
				+ proc_name + "\': " + std::to_string( S1->count )
				+ "\ndoes not match its previous declaration: "
				+ std::to_string( globals[ proc_name ].arity )
				+ ".\nThe first declaration of the procedure was on the line "
				+ globals[ proc_name ].line + '\n';
			// количество аргументов определяемой процедуры _: _ не совпадает с её предыдущим
			// объявлением: _. Первое объявление процедуры было на строке _
			// the number of arguments of the procedure being defined _: _ does not match its previous
			// declaration: _. The first declaration of the procedure was on the line _
			return 1;
		}
	}
	return 0;}
int tSM::p79(){ //  PCBODY -> E
	return 0;}
int tSM::p80(){ //  PCBODY -> INTER PCBODY
	return 0;}
int tSM::p81(){ //  PCBODY -> VAR PCBODY
	return 0;}
int tSM::p82(){ //   PCPAR -> ( define ( $id
	locals.clear();
	S1->name = S4->name;
	S1->count = 0;
	S1->types = 0;
	scope = LOCAL_SC;
	std::string proc_name = S4->name;
	if( globals[ proc_name ].test( BUILT ) ) {
		std::string built_unit_type = globals[ proc_name ].test( VAR ) ?
			"variable" : "function";
		ferror_message +=
			"Error[82-1] in line " + S2->line
			+ ": the name of the built-in "
			+ ( globals[ proc_name ].test( VAR ) ? "variable" : "function" )
			+ " \'"
			+ proc_name + "\'\nis used as the name of the procedure being defined\n";
		// имя встроенной переменной/функции используется в качестве имени определяемой процедуры
		// the name of the built-in variable/function _ is used as the name of the procedure being defined
		return 1;
	} else if( globals[ proc_name ].test( DEFINED ) ) {
		ferror_message +=
			"Error[82-2] in line " + S2->line
			+ ": the name of the predicate being defined \'"
			+ proc_name + "\'\nhas already been used previously to define a "
			+ ( globals[ proc_name ].test( VAR ) ? "variable" : "function" )
			+ ".\nThe first mention of this name was on the "
			+ globals[ proc_name ].line + " line.\n";
			// имя определяемого предиката _ уже было использовано ранее для определения
			// переменной/функции.
			// Первое упоминание данного имени было на _ строке.
			// the name of the predicate being defined _ has already been used
			// previously to define a variable/function.
			// The first mention of this name was on the _ line.
		return 1;
	} else if( globals[ proc_name ].test( VAR ) ) {
		ferror_message +=
			"Error[82-3] in line " + S2->line
			+ ": the name of the predicate being defined \'"
			+ proc_name + "\'\nhas already been used as a global variable"
			+ ".\nThe first mention of this name was on the "
			+ globals[ proc_name ].line + " line.\n";
		// имя определяемого предиката _ уже было использовано как глобальная переменная.
		// Первое упоминание данного имени было на _ строке.
		// the name of the predicate being defined _ has already been used as a global variable.
		// The first mention of this name was on the _ line
		return 1;
	}
	return 0;}
int tSM::p83(){ //   PCPAR -> PCPAR $id
    if( locals.count( S2->name ) ){
		ferror_message +=
			"Error[83-1] in line " + S2->line
			+ ": when defining the procedure \'"
			+ S1->name
			+ "\',\nthe name of the argument is duplicated: \'"
			+ S2->name + "\'\n";
		// при определении процедуры _ дублируется имя аргумента _
		// when defining the procedure _, the name of the argument is duplicated _
		return 1;
    }
    if( S2->name == S1->name ){
		ferror_message +=
			"Warning[83-2] in line "+ S2->line +": when defining the predicate \'"
			+ S1->name +
			"\'\none of the arguments duplicates the name of the predicate\n";
		// при определении предиката _ один из аргументов
		// дублирует имя предиката
		// when defining the predicate _, one of the arguments
		// duplicates the name of the predicate
    }
    locals.insert( S2->name );
	++S1->count;
	return 0;}
//_____________________
int tSM::p84(){return 0;} int tSM::p85(){return 0;} 
int tSM::p86(){return 0;} int tSM::p87(){return 0;} 
int tSM::p88(){return 0;} int tSM::p89(){return 0;} 
int tSM::p90(){return 0;} int tSM::p91(){return 0;} 
int tSM::p92(){return 0;} int tSM::p93(){return 0;} 
int tSM::p94(){return 0;} int tSM::p95(){return 0;} 
int tSM::p96(){return 0;} int tSM::p97(){return 0;} 
int tSM::p98(){return 0;} int tSM::p99(){return 0;} 
int tSM::p100(){return 0;} int tSM::p101(){return 0;} 
int tSM::p102(){return 0;} int tSM::p103(){return 0;} 
int tSM::p104(){return 0;} int tSM::p105(){return 0;} 
int tSM::p106(){return 0;} int tSM::p107(){return 0;} 
int tSM::p108(){return 0;} int tSM::p109(){return 0;} 
int tSM::p110(){return 0;} 

