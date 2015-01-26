/*
 * engine.c
 *
 *  Created on: ??ş/??ş/????
 *      Author: Osama
 */


#include "engine.h"
#include "malloc.h"


engine main_engine;


SGLIB_DEFINE_QUEUE_FUNCTIONS(engine,connection*,tasks,i,j,main_engine.queue_size);

cresult circus_engine_notify(connection* con)
{
	pthread_mutex_lock(&main_engine.mtx);
	sglib_engine_add(&main_engine,con);
	pthread_mutex_unlock(&main_engine.mtx);
	return CIRCUS_RESULT_SUCCESS;
}

void circus_engine_thread_proc(void* conrxt)
{

	connection* c;

	int loop =1;
	while(loop)
	{

		pthread_mutex_lock(&main_engine.mtx);
		c=0;
		loop =0;
		if(!sglib_engine_is_empty(&main_engine))
		{
			c= sglib_engine_first_element(&main_engine);
			sglib_engine_delete(&main_engine);
			loop=1;
		}



		pthread_mutex_unlock(&main_engine.mtx);

		if(c)
		{
			component* comp= (component*) (c->dest);

			pthread_mutex_lock(&c->mtx);
			c->f.flags.triggered=0;
			pthread_mutex_unlock(&c->mtx);
			comp->vtbl->act(c->dest,c);
		}
	}
}


cresult circus_engine_start(cenginestartmode esm)
{

	int i=0;
	for(i=0;i<main_engine.thread_size;i++)
	{
		pthread_create(&main_engine.thrds[i],0,(void*(*)(void*))circus_engine_thread_proc,0);
		if (esm == CIRCUS_ENGINE_STARTMODE_SYNC)
			pthread_join(main_engine.thrds[i],NULL);
	}
	return CIRCUS_RESULT_SUCCESS;
}

cresult circus_engine_initialize(csize queue_size,csize threads)
{
	main_engine.tasks = (connection**)malloc(sizeof(connection*)*queue_size);
	main_engine.queue_size = queue_size;
	main_engine.thrds = (pthread_t*)malloc(sizeof(pthread_t)*threads) ;
	main_engine.thread_size = threads;
	pthread_mutex_init(&main_engine.mtx,0);
	return CIRCUS_RESULT_SUCCESS;

}
