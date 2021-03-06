/*
 * builder.h
 *
 *  Created on: ??�/??�/????
 *      Author: Osama
 */

#ifndef BUILDER_H_
#define BUILDER_H_


#include "component.h"
//#include "global.h"

typedef struct _module_component
{
	cstring name;
	component* comp;
	cchar color;
	struct _module_component* right;
	struct _module_component* left;
}module_component;

module_component* global_module_component_list;

#define CB_COMPARATOR(x,y) (strcmp(x->name,y->name))

SGLIB_DEFINE_RBTREE_PROTOTYPES(module_component, left, right, color, CB_COMPARATOR);

cresult CIRCUS_API_ENTRY circus_modulecomponent_init();
cresult CIRCUS_API_ENTRY circus_modulecomponent_add(module_component** mc,cstring compname,cstring name,cstring extra);
cresult CIRCUS_API_ENTRY circus_modulecomponent_initialize(module_component** mc);
cresult CIRCUS_API_ENTRY circus_modulecomponent_connect(module_component** mc,cstring srccomp,
											cstring srcpin,
											cstring destcomp,
											cstring destpin);
cresult CIRCUS_API_ENTRY circus_modulecomponent_prepare(module_component** mc);





#endif /* BUILDER_H_ */
