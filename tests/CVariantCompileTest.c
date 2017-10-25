/*! \file
 *
 * \date Created on: 25.10.2017
 * \author jochen.ulrich
 */

#include "HttpStatusCodes_C.h"

#include "string.h"
#include "stdio.h"

#define TEST(predicate)                            \
	if ( !(predicate) )                            \
	{                                              \
		printf("TEST(" #predicate ") failed");     \
		return 1;                                  \
	}

int main(int argc, char** argv)
{
	TEST((int)HttpStatus_OK == 200)
	TEST(strcmp(HttpStatus_reasonPhrase(HttpStatus_NotFound), "Not Found") == 0)
	TEST(HttpStatus_isInformational(HttpStatus_Continue))
	TEST(HttpStatus_isSuccessful(HttpStatus_Created))
	TEST(HttpStatus_isRedirection(HttpStatus_SeeOther))
	TEST(HttpStatus_isClientError(HttpStatus_Gone))
	TEST(HttpStatus_isServerError(HttpStatus_BadGateway))
	TEST(HttpStatus_isError(HttpStatus_UnprocessableEntity))

	return 0;
}
