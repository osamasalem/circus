/*
 ============================================================================
 Name        : main.c
 Author      : Osama Salem
 Version     :
 Copyright   : GNU General Public License
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"

#include "pin.h"
#include "engine.h"
#include "samplecomps.h"
#include "builder.h"
#include "hash.h"
#include <string.h>
#include <conio.h>

#include <pthread.h>


int CIRCUS_API_ENTRY entry(void) {


			/*
	inputpin_cint pin1;
	outputpin_cint pin2;

	circus_inputpin_cint_init(0,&pin1,0);
	circus_outputpin_cint_init(0,&pin2);

	circus_pin_connect(&pin1.ipin, &pin2.opin);

	printf("%d\n",sizeof(inputpin_cint));
	printf("%d\n",sizeof(outputpin_cint));

	printf("%d\n",pin1.ipin.pin.meta->type);
	printf("%d\n",pin1.ipin.pin.meta->dir);
	printf("%d\n\n",pin1.ipin.pin.meta->size);

	printf("%d\n",pin2.opin.pin.meta->type);
	printf("%d\n",pin2.opin.pin.meta->dir);
	printf("%d\n",pin2.opin.pin.meta->size);
	*/

	module_component* mc=0;

	circus_engine_initialize(1000,1);
	circus_componentfactory_initialize();
	circus_componentfactory_register("com.circus.std.counter",mycomp1_getinstance);
	circus_componentfactory_register("com.circus.io.print",mycomp2_getinstance);
	circus_modulecomponent_add(&mc,"com.circus.std.counter","x1","linear");
	circus_modulecomponent_add(&mc,"com.circus.io.print","x2","stdout");
	circus_componentfactory_cleanup();
//	circus_modulecomponent_initialize(&mc);
	circus_modulecomponent_connect(&mc,"x1","out","x2","in");
	circus_modulecomponent_prepare(&mc);
	circus_engine_start(CIRCUS_ENGINE_STARTMODE_SYNC);
	getch();
	/*
	int i;
	__sync_fetch_and_add(&i,1);

	int a[8] = {0,1,2,3,4};
	int i;
	for ( i=0;i<8;i++)
	{
		printf("%d",a[i]);
	}
	//printf("%x\n",circus_hash_data("Osama",6));

	component_factory* p = circus_object_create(component_factory);
	circus_object_refer(p);
	circus_object_release(p);
	circus_object_release(p);
	*/




	return 0;
}
