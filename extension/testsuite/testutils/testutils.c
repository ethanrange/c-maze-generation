#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#include "testutils.h"


void testcond( bool condition, char *testname )
{
	if( condition )
	{
		printf( "T %s: OK\n", testname );
	} else
	{
		printf( "T %s: FAIL\n", testname );
	}
}

void testint( int got, int expected, char *testname )
{
	if( expected==got )
	{
		printf( "T %s == %d: OK\n", testname, expected );
	} else
	{
		printf( "T %s (expected=%d, got=%d): FAIL\n",
			testname, expected, got );
	}
}

void testchar( char got, char expected, char *testname )
{
	if( expected==got )
	{
		printf( "T %s == %c, code %d: OK\n",
			testname, expected, expected );
	} else
	{
		printf( "T %s (expected=%c (code %d), got=%c (code %d)): FAIL\n",
			testname, expected, expected, got, got );
	}
}


void testlong( long got, long expected, char *testname )
{
	if( expected==got )
	{
		printf( "T %s == %ld: OK\n", testname, expected );
	} else
	{
		printf( "T %s (expected=%ld, got=%ld): FAIL\n",
			testname, expected, got );
	}
}

void testdouble( double got, double expected, char *testname )
{
	if( expected==got )
	{
		printf( "T %s == %g: OK\n", testname, expected );
	} else
	{
		printf( "T %s (expected=%g, got=%g): FAIL\n",
			testname, expected, got );
	}
}

void teststring( char *got, char *expected, char *testname )
{
	assert( got != NULL );
	assert( expected != NULL );
	if( strcmp(expected,got)==0 )
	{
		printf( "T %s == '%s': OK\n", testname, expected );
	} else
	{
		printf( "T %s (expected='%s', got='%s'): FAIL\n",
			testname, expected, got );
	}
}
