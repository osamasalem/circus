/*
 * connection.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "connection.h"
#include "pin.h"
#include "engine.h"

#include <memory.h>
#include <stdlib.h>



connection* circus_connection_create(typemeta* tm)
{

	connection* con;

	csize totalsize = 1;

	int i;
	for(i=0;tm->size[i]>1;i++)
		totalsize *= tm->size[i];

	switch(tm->type)
	{
		case CIRCUS_TYPE_INVALID:return 0;
		case CIRCUS_TYPE_INTEGER:	con= CIRCUS_CONNECTION_ALLOC(cint,totalsize);break;
		case CIRCUS_TYPE_LONG:		con= CIRCUS_CONNECTION_ALLOC(clong,totalsize);break;
		case CIRCUS_TYPE_BOOL:		con= CIRCUS_CONNECTION_ALLOC(cbool,totalsize);break;
		case CIRCUS_TYPE_FLOAT:		con= CIRCUS_CONNECTION_ALLOC(cfloat,totalsize);break;
		case CIRCUS_TYPE_CHAR:		con= CIRCUS_CONNECTION_ALLOC(cchar,totalsize);break;
		case CIRCUS_TYPE_DOUBLE :	con= CIRCUS_CONNECTION_ALLOC(cdouble,totalsize);break;
		case CIRCUS_TYPE_REFERENCE:	con= CIRCUS_CONNECTION_ALLOC(cptr,totalsize);break;
		case CIRCUS_TYPE_STRING:	con= CIRCUS_CONNECTION_ALLOC(cstring,totalsize);break;
		default: return 0;
	}

	pthread_mutex_init(&con->mtx,0);
	con->f.w=0;
	con->dest =0;
	return con;
}

//CIRCUS_CONNECTION_FUNC_DEF(cint)
CIRCUS_CONNECTION_FUNC_DEF(cfloat)
CIRCUS_CONNECTION_FUNC_DEF(cbool)
CIRCUS_CONNECTION_FUNC_DEF(cchar)
CIRCUS_CONNECTION_FUNC_DEF(clong)
CIRCUS_CONNECTION_FUNC_DEF(cptr)
CIRCUS_CONNECTION_FUNC_DEF(cdouble)
CIRCUS_CONNECTION_FUNC_DEF(clonglong)

cresult circus_pin_setcint(connection* conc,cint value)
{
	connection_cint* con = (connection_cint*)conc;
	pthread_mutex_lock(&con->conn.mtx);
	con->data[0]=value;
	if(!con->conn.f.flags.triggered)
	{
		con->conn.f.flags.triggered = 1;
		circus_engine_notify(conc);

	}
	con->conn.f.flags.initd=1;
	pthread_mutex_unlock(&con->conn.mtx);
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_pin_getcint(connection* conc,cint* pvalue)
{
	connection_cint* con = (connection_cint*)conc;
	cresult res=CIRCUS_RESULT_SUCCESS;
	pthread_mutex_lock(&con->conn.mtx);
	*pvalue = con->data[0];
	if(con->conn.f.flags.initd)res=CIRCUS_RESULT_FAIL;
	pthread_mutex_unlock(&con->conn.mtx);
	return res;
}


cresult circus_pin_setcstring(connection* conc,cstring value)
{
	connection_cstring* con = (connection_cstring*)conc;
	pthread_mutex_lock(&con->conn.mtx);
	if(con->data[0])free(con->data);
	con->data[0]=strdup(value);
	if(!con->conn.f.flags.triggered)
	{
		con->conn.f.flags.triggered = 1;
	}
	con->conn.f.flags.initd=1;
	pthread_mutex_unlock(&con->conn.mtx);
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_pin_getcstring(connection* conc,cstring* pvalue)
{
	connection_cstring* con = (connection_cstring*)conc;
	cresult res=CIRCUS_RESULT_SUCCESS;
	pthread_mutex_lock(&con->conn.mtx);
	strcpy(*pvalue,con->data[0]);
	if(con->conn.f.flags.initd)res=CIRCUS_RESULT_FAIL;
	pthread_mutex_unlock(&con->conn.mtx);
	return res;
}

cresult circus_pin_setarraycstring(connection* conc,cstring* pvalue,csize size)
{
	connection_cstring* con = (connection_cstring*)conc;
	pthread_mutex_lock(&con->conn.mtx);
	int i;
	for(i=0;i<size;i++)
	{
		if(con->data[i])
			free((void*)con->data);
		con->data[i]=strdup(pvalue[i]);
	}

	if(!con->conn.f.flags.triggered)
	{
		con->conn.f.flags.triggered = 1;
	}
	con->conn.f.flags.initd=1;
	pthread_mutex_unlock(&con->conn.mtx);
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_pin_getarraycstring(connection* conc,cstring* pvalue,csize size)
{
	connection_cstring* con = (connection_cstring*)conc;
	cresult res=CIRCUS_RESULT_SUCCESS;
	pthread_mutex_lock(&con->conn.mtx);
	int i;
	for(i=0;i<size;i++)
		strcpy(pvalue[i],con->data[i]);

	if(con->conn.f.flags.initd)res=CIRCUS_RESULT_FAIL;
	pthread_mutex_unlock(&con->conn.mtx);
	return res;
}

