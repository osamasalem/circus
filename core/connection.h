/*
 * connection.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_


#include "component.h"
#include "pin.h"
#include "global.h"
#include "object.h"

#include <pthread.h>



typedef union _cflags
{
	cword w;
	struct _inner_flags
	{
		cbool triggered	: 1;
		cbool initd		: 1;
	}flags;
}cflags ;


//typedef struct _component component;

struct _connection
{
	object obj;
	component* dest;
	cflags f;
	pthread_mutex_t mtx;
};

//typedef struct _typemeta typemeta;


connection* circus_connection_create(struct _typemeta* tm);



#define TYPED_CONNECTION(__TYPE)		\
typedef struct _connection_##__TYPE		\
{										\
	connection conn;					\
	__TYPE data[0];						\
}connection_##__TYPE;



TYPED_CONNECTION(cint)
TYPED_CONNECTION(cfloat)
TYPED_CONNECTION(cbool)
TYPED_CONNECTION(cchar)
TYPED_CONNECTION(clong)
TYPED_CONNECTION(cptr)
TYPED_CONNECTION(cdouble)
TYPED_CONNECTION(clonglong)
TYPED_CONNECTION(cstring)


#define CIRCUS_CONNECTION_ALLOC(TYPE,SIZE) ((connection*)malloc(CIEL4(sizeof(connection)+(SIZE*sizeof(TYPE)))));


#define CIRCUS_CONNECTION_FUNC_DECL(TYPE)						\
cresult circus_pin_set##TYPE(connection* conc,TYPE value);\
cresult circus_pin_get##TYPE(connection* conc,TYPE* pvalue);\
cresult circus_pin_set_array##TYPE(connection* conc,TYPE* pvalue,csize size);\
cresult circus_pin_get_array##TYPE(connection* conc,TYPE* pvalue,csize size);


CIRCUS_CONNECTION_FUNC_DECL(cint)
CIRCUS_CONNECTION_FUNC_DECL(cfloat)
CIRCUS_CONNECTION_FUNC_DECL(cbool)
CIRCUS_CONNECTION_FUNC_DECL(cchar)
CIRCUS_CONNECTION_FUNC_DECL(clong)
CIRCUS_CONNECTION_FUNC_DECL(cptr)
CIRCUS_CONNECTION_FUNC_DECL(cdouble)
CIRCUS_CONNECTION_FUNC_DECL(clonglong)
CIRCUS_CONNECTION_FUNC_DECL(cstring)


#define CIRCUS_CONNECTION_FUNC_DEF(TYPE)						\
cresult circus_pin_set##TYPE(connection* conc,TYPE value)	\
{	\
	connection_##TYPE* con = (connection_##TYPE*)conc;\
	pthread_mutex_lock(&con->conn.mtx);							\
	con->data[0]=value;											\
	if(!con->conn.f.flags.triggered)							\
	{															\
		con->conn.f.flags.triggered = 1;						\
	}															\
	con->conn.f.flags.initd=1;									\
	pthread_mutex_unlock(&con->conn.mtx);						\
	return CIRCUS_RESULT_SUCCESS;								\
}																\
\
cresult circus_pin_get##TYPE(connection* conc,TYPE* pvalue)\
{\
	connection_##TYPE* con = (connection_##TYPE*)conc;\
	cresult res=CIRCUS_RESULT_SUCCESS;\
	pthread_mutex_lock(&con->conn.mtx);\
	*pvalue = con->data[0];\
	if(con->conn.f.flags.initd)res=CIRCUS_RESULT_FAIL;\
	pthread_mutex_unlock(&con->conn.mtx);\
	return res;\
}\
\
cresult circus_pin_set_array##TYPE(connection* conc,TYPE* pvalue,csize size)\
{\
	connection_##TYPE* con = (connection_##TYPE*)conc;\
	pthread_mutex_lock(&con->conn.mtx);\
	memcpy(con->data,pvalue,size*sizeof(TYPE));\
	if(!con->conn.f.flags.triggered)\
	{\
		con->conn.f.flags.triggered = 1;\
	}\
	con->conn.f.flags.initd=1;\
	pthread_mutex_unlock(&con->conn.mtx);\
	return CIRCUS_RESULT_SUCCESS;\
}\
\
cresult circus_pin_get_array##TYPE(connection* conc,TYPE* pvalue,csize size)\
{\
	connection_##TYPE* con = (connection_##TYPE*)conc;\
	cresult res=CIRCUS_RESULT_SUCCESS;\
	pthread_mutex_lock(&con->conn.mtx);\
	memcpy(pvalue,con->data,size*sizeof(TYPE));\
	if(con->conn.f.flags.initd)res=CIRCUS_RESULT_FAIL;\
	pthread_mutex_unlock(&con->conn.mtx);\
	return res;\
}


///typedef enum _ctype ctype;




#endif /* CONNECTION_H_ */
