/*
 * engine.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Osama
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <pthread.h>

#include "sglib.h"
#include "global.h"
#include "component.h"

typedef enum _cenginestartmode
{
	CIRCUS_ENGINE_STARTMODE_SYNC,
	CIRCUS_ENGINE_STARTMODE_ASYNC
}cenginestartmode;

typedef struct _engine
{
	pthread_mutex_t mtx;
	pthread_t* thrds;
	connection** tasks;
	csize queue_size;
	csize thread_size;
	csize i; 			//I used to name my vars by meaningful names ...blame SGLIB
	csize j;
}engine;

extern engine main_engine;

cresult circus_engine_initialize(csize qsize,csize threads);
cresult circus_engine_start(cenginestartmode esm );
cresult circus_engine_notify(connection* con);


#endif /* ENGINE_H_ */
