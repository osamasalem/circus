/*
 * samplecomps.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "pin.h"
#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////
// MyComp 1
/////////////////////////////////////////////////////////////
typedef struct _mycomp1
{
	component c;
	pin hin;
	pin hout;
	pin out;
}mycomp1;

cresult mycomp1_getpinbyname(component* c,cstring name,pinmeta* pm)
{
	mycomp1* comp =(mycomp1*)c;

	if(!strcmp(name,"out"))
	{
		circus_pinmeta_fill(pm,(component*)comp,&comp->out,CIRCUS_TYPE_INTEGER,0,CIRCUS_DIRECTION_OUT);
		return CIRCUS_RESULT_SUCCESS;
	}

	if(!strcmp(name,"hin"))
	{
		circus_pinmeta_fill(pm,(component*)comp,&comp->hin,CIRCUS_TYPE_INTEGER,0,CIRCUS_DIRECTION_IN);
		return CIRCUS_RESULT_SUCCESS;
	}

	if(!strcmp(name,"hout"))
	{
		circus_pinmeta_fill(pm,(component*)comp,&comp->hout,CIRCUS_TYPE_INTEGER,0,CIRCUS_DIRECTION_OUT);
		return CIRCUS_RESULT_SUCCESS;
	}

	return CIRCUS_RESULT_FAIL;
}


cresult mycomp1_initialize(component* c)
{
	mycomp1* comp =(mycomp1*)c;
	comp->hin=0;
	comp->hout=0;
	comp->out=0;

	pinmeta pmhout,pmhin;
	mycomp1_getpinbyname(c,"hin",&pmhin);
	mycomp1_getpinbyname(c,"hout",&pmhout);
	circus_pin_connect(&pmhin,&pmhout);

	return CIRCUS_RESULT_SUCCESS;
}
cresult mycomp1_prepare(component* c)
{
	mycomp1* comp =(mycomp1*)c;

	if(comp->out)circus_pin_setcint(comp->out,5);
	if(comp->hout)circus_pin_setcint(comp->hout,5);

	return CIRCUS_RESULT_SUCCESS;
}

void mycomp1_act(component* c,pin* p)
{
	mycomp1* comp =(mycomp1*)c;
	cint i;
	circus_pin_getcint(comp->hin,&i);
	i++;
	if (i<100)
	{
		if(comp->out)circus_pin_setcint(comp->out,i);
		if(comp->hout)circus_pin_setcint(comp->hout,i);

	}

}


component_vtbl mycomp1_vtbl={
		mycomp1_prepare,
		mycomp1_getpinbyname,
		mycomp1_act
};


component* mycomp1_getinstance(cstring param)
{
	mycomp1* comp;
	comp = malloc(sizeof(mycomp1));
	comp->c.vtbl = &mycomp1_vtbl;
	comp->hin=0;
	comp->hout=0;
	comp->out=0;

	pinmeta pmhout,pmhin;
	mycomp1_getpinbyname(&comp->c,"hin",&pmhin);
	mycomp1_getpinbyname(&comp->c,"hout",&pmhout);
	circus_pin_connect(&pmhin,&pmhout);

	return (component*)comp;
}


//////////////////////////////////////////////////////////////
// MyComp 2
/////////////////////////////////////////////////////////////
typedef struct _mycomp2
{
	component c;
	pin in;
}mycomp2;

cresult mycomp2_getpinbyname(component* c,cstring name,pinmeta* pm)
{

	mycomp2* comp =(mycomp2*)c;
	if(!strcmp(name,"in"))
	{
		circus_pinmeta_fill(pm,(component*)comp,&comp->in,CIRCUS_TYPE_INTEGER,0,CIRCUS_DIRECTION_IN);
		return CIRCUS_RESULT_SUCCESS;
	}


	return CIRCUS_RESULT_SUCCESS;
}


cresult mycomp2_initialize(component* c)
{
	mycomp2* comp =(mycomp2*)c;
	comp->in=0;
	return CIRCUS_RESULT_SUCCESS;
}


cresult mycomp2_prepare(component* c)
{
	return CIRCUS_RESULT_SUCCESS;
}

void mycomp2_act(component* c,pin* p)
{
	mycomp2* comp =(mycomp2*)c;
	cint i;
	circus_pin_getcint(comp->in,&i);
	printf("%d\n",(int)i);

}


component_vtbl mycomp2_vtbl={
		mycomp2_prepare,
		mycomp2_getpinbyname,
		mycomp2_act
};

component* mycomp2_getinstance(cstring param)
{
	mycomp2* comp;
	comp = (mycomp2*)malloc(sizeof(mycomp2));
	comp->c.vtbl = &mycomp2_vtbl;
	comp->in=0;
	return (component*)comp;
}


