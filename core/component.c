/*
 * component.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "global.h"
#include "component.h"
#include "stdlib.h"

SGLIB_DEFINE_RBTREE_FUNCTIONS(component_factory, left, right, color, CF_COMPARATOR);

cresult circus_componentfactory_initialize()
{
	component_factory_list = 0;
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_componentfactory_register(cstring name,component* (*getInstance)())
{
	component_factory cf;
	component_factory* pcf;

	cf.name = name;
	pcf = sglib_component_factory_find_member(component_factory_list,&cf);
	if (!pcf)
	{
		pcf = circus_object_create(component_factory);
		pcf->name=name;
		pcf->getinstance = getInstance;
		sglib_component_factory_add(&component_factory_list,pcf);

		return CIRCUS_RESULT_SUCCESS;
	}
	return CIRCUS_RESULT_FAIL;
}

component* circus_componentfactory_getinstanceof(cstring name,cstring param)
{
	component_factory cfi;
	component_factory* pcf=0;

	cfi.name = name;
	pcf = sglib_component_factory_find_member(component_factory_list,&cfi);
	if(!pcf)
		return 0;

	return pcf->getinstance(param);

}

cresult circus_componentfactory_cleanup()
{
	component_factory* cf;
	while(component_factory_list)
	{
		cf = component_factory_list;
		sglib_component_factory_delete(&component_factory_list,component_factory_list);
		circus_object_release(cf);
	}
	return CIRCUS_RESULT_SUCCESS;
}
