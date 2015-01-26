/*
 * pin.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "pin.h"

cresult circus_pinmeta_isequal(typemeta* tm1,typemeta* tm2)
{
	if (tm1->type != tm2->type)
			return CIRCUS_RESULT_FAIL;
	//TODO: Array Check

	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_pin_connect(pinmeta* pm1,pinmeta* pm2)
{
	pinmeta* ipm = NULL;
	pinmeta* opm = NULL;
	connection* con;

	if(pm1->dir == CIRCUS_DIRECTION_IN &&
		pm2->dir == CIRCUS_DIRECTION_OUT)
	{
		ipm=pm1;
		opm=pm2;
	}
	else if(pm2->dir == CIRCUS_DIRECTION_IN &&
		pm1->dir == CIRCUS_DIRECTION_OUT)
	{
		ipm=pm2;
		opm=pm1;
	}
	else return CIRCUS_RESULT_FAIL;

	if(circus_pinmeta_isequal(&pm1->tm,&pm2->tm)==
			CIRCUS_RESULT_FAIL)
		return CIRCUS_RESULT_FAIL;

	con = circus_connection_create(&ipm->tm);

	*(opm->ppin)=con;
	*(ipm->ppin)=con;
	con->dest = ipm->cmponent;

	return CIRCUS_RESULT_SUCCESS;
}

inline void circus_pinmeta_fill(pinmeta* pm,component* cmp,pin* pin,ctype type,clong extra,cpindirection dir)
{
	pm->tm.type= type;
	pm->dir= dir;
	pm->cmponent = cmp;
	int i;
	for (i=0;i<MAX_ARRAY_DIMENSIONS;i++)
		pm->tm.size[i]=1;
	pm->ppin = pin;
}
