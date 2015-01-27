/*
 * builder.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "builder.h"
#include <stdlib.h>
#include <string.h>

SGLIB_DEFINE_RBTREE_FUNCTIONS(module_component, left, right, color, CB_COMPARATOR);

cresult circus_modulecomponent_init()
{
	global_module_component_list =0;
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_modulecomponent_add(module_component** mc,cstring compname,cstring name,cstring extra)
{
	module_component u;
	module_component* pu;
	component* comp;

	if(!mc)
		mc = &global_module_component_list;

	u.name = name;
	pu = sglib_module_component_find_member(*mc,&u);
	if (!pu)
	{
		comp= circus_componentfactory_getinstanceof(compname,extra);
		if(!comp)
			return CIRCUS_RESULT_FAIL;
		pu = (module_component*)malloc(sizeof(module_component));
		pu->name=name;
		pu->comp=comp;
		sglib_module_component_add(mc,pu);
		return CIRCUS_RESULT_SUCCESS;
	}
	return CIRCUS_RESULT_FAIL;
}

cresult circus_modulecomponent_initialize(module_component** mc)
{
	struct sglib_module_component_iterator uit;
	module_component* u;

	if(!mc)
		mc = &global_module_component_list;


	for(u=sglib_module_component_it_init(&uit,*mc);
			u!=NULL;
			u=sglib_module_component_it_next(&uit))
	{
		//u->comp->vtbl->initialize(u->comp);
	}
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_modulecomponent_connect(module_component** mc,
											cstring srccomp,
											cstring srcpin,
											cstring destcomp,
											cstring destpin)
{
	module_component u;
	module_component* pu1;
	module_component* pu2;

	pinmeta pm1;
	pinmeta pm2;


	if(!mc)
			mc = &global_module_component_list;

	u.name = srccomp;
	pu1=sglib_module_component_find_member(*mc,&u);
	if(!pu1)
		return CIRCUS_RESULT_FAIL;

	u.name = destcomp;
	pu2=sglib_module_component_find_member(*mc,&u);
	if(!pu2)
		return CIRCUS_RESULT_FAIL;

	pu1->comp->vtbl->getpinbyname((component*)pu1->comp,srcpin,&pm1);
	pu2->comp->vtbl->getpinbyname((component*)pu2->comp,destpin,&pm2);
	circus_pin_connect(&pm1,&pm2);
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_modulecomponent_prepare(module_component** mc)
{
	struct sglib_module_component_iterator uit;
	module_component* u;

	if(!mc)
		mc = &global_module_component_list;


	for(u=sglib_module_component_it_init(&uit,*mc);
			u!=NULL;
			u=sglib_module_component_it_next(&uit))
	{
		u->comp->vtbl->prepare(u->comp);
	}
	return CIRCUS_RESULT_SUCCESS;
}
