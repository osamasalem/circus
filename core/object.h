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
		((__type*)circus_object_create_size( sizeof(__type) ) )

cptr circus_object_create_size(csize size);

void inline circus_object_refer(cptr p);
void circus_object_release(cptr p);

void inline circus_object_lock(cptr p);
void inline circus_object_unlock(cptr p);


#endif /* OBJECT_H_ */
