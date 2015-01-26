/*
 * component.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "object.h"
#include "types.h"
#include "pin.h"
#include "global.h"
#include "sglib.h"

//typedef struct _connection *pin;
//typedef struct _pinmeta pinmeta;

//struct _component component;
//struct _component ;
//struct _pinmeta;
//struct _pin;

//typedef struct _component component;

struct _component_vtbl
{
	cresult (*initialize)(component* c);
	cresult (*prepare)(component* c);
	cresult (*getpinbyname)(component* c,cstring name,struct _pinmeta* pm);
	void (*act)(component* c,pin* p);

};

struct _component
{
	component_vtbl* vtbl;
};

struct _component_factory
{
	//object obj;
	cstring name;
	cchar color;
	component* (*getinstance)();
	struct _component_factory* right;
	struct _component_factory* left;
};

component_factory* component_factory_list;

#define CF_COMPARATOR(x,y) (strcmp((const char*)x,(const char*)y))

SGLIB_DEFINE_RBTREE_PROTOTYPES(component_factory, left, right, color, CF_COMPARATOR);

cresult circus_componentfactory_initialize();
cresult circus_componentfactory_register(cstring name,component* (*getInstance)());
component* circus_componentfactory_getinstanceof(cstring name);
cresult circus_componentfactory_cleanup();

#endif /* COMPONENT_H_ */
