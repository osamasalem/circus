/*
 * module.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "sglib.h"

typedef struct _module_scheme_pin
{
	cstring name;
	typemeta tm;
	struct _module_scheme_pin* next;
}module_scheme_pin;

#define COMP_MSPIN(x,y) (strcmp(x->name,y->name))
SGLIB_DEFINE_LIST_PROTOTYPES(module_scheme_pin,COMP_MSP,next)

typedef struct _module_scheme_component
{
	cstring name;
	cstring type;
	struct _module_scheme_component* next;
}module_scheme_component;

#define COMP_MSCOMP(x,y) (strcmp(x->name,y->name))
SGLIB_DEFINE_LIST_PROTOTYPES(module_scheme_component,COMP_MSCOMP,next)

typedef struct _module_scheme_connection
{
	cstring srccomp;
	cstring srcpin;
	cstring dstcomp;
	cstring dstpin;
	struct _module_scheme_connection* next;
}module_scheme_connection;

#define COMP_MSCON(x,y) (strcmp(x->name,y->name))
SGLIB_DEFINE_LIST_PROTOTYPES(module_scheme_connection,COMP_MSCON,next)

typedef struct _module_scheme
{
	cstring name;
	module_scheme_pin* mod_schm_pin;
	module_scheme_component* mod_schm_comps;
	module_scheme_connection* mod_schm_conns;
	cint numofpins;

	cchar color;
	struct _module_scheme* right;
	struct _module_scheme* left;

}module_scheme;

module_scheme* global_module_scheme;

/*
typedef struct _module
{
	component c;
	pin* pin;
}module;
*/

#endif /* MODULE_H_ */
