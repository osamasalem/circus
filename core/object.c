/*
 * object.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#include "object.h"

object* circus_object_create_size(csize size)
{
	object* p = (object*)malloc( sizeof(object) + size);
	if(p)
	{
		p->ref = 1;
		pthread_spin_init(&p->lock,0);
	}
	return (p+sizeof(object));

}

cresult circus_object_refer(cptr p)
{
	object* obj = ( p - sizeof(obj) );
	pthread_spin_lock(&obj->lock);
	obj->ref++;
	pthread_spin_unlock(&obj->lock);
	return CIRCUS_RESULT_SUCCESS;
}
cresult circus_object_release(cptr p)
{
	object* obj = ( p - sizeof(obj) );
	pthread_spin_lock(&obj->lock);
	obj->ref--;
	if(!obj->ref)
	{
		pthread_spin_unlock(&obj->lock);
		pthread_spin_destroy(&obj->lock);
		free((void*)obj);
		return CIRCUS_RESULT_SUCCESS;
	}
	pthread_spin_unlock(&obj->lock);
	return CIRCUS_RESULT_SUCCESS;
}

//cresult circus_object_lock(object* obj);
//cresult circus_object_unlock(object* obj);

