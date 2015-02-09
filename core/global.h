/*
 * global.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define NULL (0)


//((0+3)/4)*4=0
//((1+3)/4)*4=4
//((2+3)/4)*4=4
//((3+3)/4)*4=4
//((4+3)/4)*4=4
//((5+3)/4)*4=8
//((6+3)/4)*4=8
//((7+3)/4)*4=8
//((8+3)/4)*4=8

typedef long cint;
typedef float cfloat;

typedef cint cbool;
typedef char cchar;
typedef char cbyte;

typedef cint clong;
typedef void* cptr;

typedef double cdouble;
typedef long long clonglong;

typedef clong csize;
typedef clong cword;

typedef char* cstring;

#define CIEL4(i) 		( ( ( i+3 )/4 )*4 )
#define NEW(__TYPE) 	( (__TYPE*) malloc( CIEL4( sizeof( __TYPE ) ) ) )



#define GETARRAYSIZE(TYPE,NUMBER) (sizeof(TYPE)*NUMBER)

typedef enum _cresult
{
	CIRCUS_RESULT_FAIL,
	CIRCUS_RESULT_SUCCESS,
}cresult ;

typedef union _cvalue
{
	cbool b;
	clong l;
	cfloat f;
	cchar c;
	cptr p;
}cvalue;


typedef
struct _cbit {
	cbool value:1;
}cbit;

typedef union _cflags
{
	cword w;
	cbyte bytes[sizeof(cword)];
	cbit bits[sizeof(cword)*8];
}cflags ;





#define CIRCUS_ID(a,b,c,d) ( (a) | (b<<8) | (c<<16) | (d<<16) )


#endif /* GLOBAL_H_ */
