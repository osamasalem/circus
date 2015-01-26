/*
 * object.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include "types.h"
#include <pthread.h>
#include "global.h"
//#include <atomics.h>

struct _object
{
	cint ref;
	pthread_spinlock_t lock;
};

#define circus_object_create(__type) \
		(__type*)circus_object_create_size( sizeof(__type) )

cptr circus_object_create_size(csize size);

cresult circus_object_refer(cptr p);
cresult circus_object_release(cptr p);

//cresult circus_object_lock(object* obj);
//cresult circus_object_unlock(object* obj);


#endif /* OBJECT_H_ */
