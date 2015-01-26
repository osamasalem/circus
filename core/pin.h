/*
 *	Pin Related Entities and procedures
 *
 */
#ifndef PIN_H_
#define PIN_H_

#include "types.h"
#include "connection.h"
#include "component.h"
#include "global.h"

typedef enum _ctype
{
	CIRCUS_TYPE_INVALID= 0,
	CIRCUS_TYPE_INTEGER,
	CIRCUS_TYPE_LONG ,
	CIRCUS_TYPE_BOOL,
	CIRCUS_TYPE_FLOAT ,
	CIRCUS_TYPE_CHAR ,
	CIRCUS_TYPE_DOUBLE ,
	CIRCUS_TYPE_STRING ,//reserved
	CIRCUS_TYPE_REFERENCE,//reserved
	CIRCUS_TYPE_STRUCT //reserved

}ctype;


typedef enum _cpindirection
{
	CIRCUS_DIRECTION_IN,
	CIRCUS_DIRECTION_OUT
}cpindirection;

#define MAX_ARRAY_DIMENSIONS 8

//typedef struct _connection* pin;


struct _typemeta
{
	ctype type;
	csize size[MAX_ARRAY_DIMENSIONS];
};

//struct _component;



struct _pinmeta
{
	typemeta tm;
	pin* ppin;
	cpindirection dir;
	struct _component* cmponent;
};

/**
 * \fn cresult circus_pin_connect(pinmeta* pm1,pinmeta* pm2)
 * \brief Connect two pins based on Pin Meta structures
 * \param pm1 First pin Meta
 * \param pm2 Second Pin Meta
 * \return CIRCUS_RESULT_SUCCESS in case of success CIRCUS_RESULT_FAIL otherwise
 */
cresult circus_pin_connect(pinmeta* pm1,pinmeta* pm2);

/**
 * \fn void circus_pinmeta_fill(pinmeta* pm,component* cmp,pin* pin,ctype type,clong extra,cpindirection dir)
 * \brief Macro-Like function to fill pin-meta structure
 * \param pm Target pin meta structure to be filled
 * \param cmp Owner Component of this pin
 * \param pin Target pin that can be described
 * \param type pin' data type
 * \param extra (Reserved)
 * \param dir
 */
void circus_pinmeta_fill(pinmeta* pm,struct _component* cmp,pin* pin,ctype type,clong extra,cpindirection dir);

/**
 * \fn cresult circus_pinmeta_isequal(typemeta* tm1,typemeta* tm2)
 * \brief Check Pin Meta Equality
 * \param tm1 First Operand
 * \param tm2 Second Operand
 * \return CIRCUS_RESULT_SUCCESS in case of success CIRCUS_RESULT_FAIL otherwise
 **/
cresult circus_pinmeta_isequal(typemeta* tm1,typemeta* tm2);

#endif /* PIN_H_ */
