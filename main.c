/*
	Copyright © 2020 daltomi <daltomi@disroot.org>

	This file is part of sztype.

	sztype is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	sztype is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with sztype.  If not, see <http://www.gnu.org/licenses/>.
*/

/* C99 Comp. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

#include "config.h"

#define bitsizeof(type) (CHAR_BIT * sizeof(type))

#define print_bitsize(type) printf("%10s\t%ld\n", #type, bitsizeof(type))

enum select {
	ALL,
	BOOL,
	CHAR,
	SHORT,
	INT,
	LONG,
	LONG_LONG,
	FLOAT,
	DOUBLE,
	POINTER,
	UNKNOWN,
};

char const* const options[] = {
	[ALL]		= "all",
	[BOOL]		= "bool",	/* begin ctypes */
	[CHAR]		= "char",
	[SHORT]		= "short",
	[INT]		= "int",
	[LONG]		= "long",
	[LONG_LONG]	= "long long",
	[FLOAT]		= "float",
	[DOUBLE]	= "double",
	[POINTER]	= "pointer",
	[UNKNOWN]	= "unknown",
	NULL
};

void print_ctype(enum select const type)
{
	typedef void* pointer;

	switch (type) {
	case BOOL       : print_bitsize(bool);		break;
	case CHAR       : print_bitsize(char);		break;
	case SHORT      : print_bitsize(short);		break;
	case INT        : print_bitsize(int);		break;
	case LONG       : print_bitsize(long);		break;
	case LONG_LONG  : print_bitsize(long long);	break;
	case FLOAT      : print_bitsize(float);		break;
	case DOUBLE     : print_bitsize(double);	break;
	case POINTER    : print_bitsize(pointer);	break;
	default         : assert(0);
	};
}

void print_all_ctype(void)
{
	for (enum select ctype = BOOL; ctype < UNKNOWN; ++ctype) {
		print_ctype(ctype);
	}
}

void print_all_options(void)
{
	for (enum select option = ALL; option < UNKNOWN; ++option) {
		printf("\t\"%s\"\n", options[option]);
	}
}

void print_help(void)
{
	printf("\nUsage: %s [type]\n\nValid types:\n", APP_NAME);
	print_all_options();
}

enum select print_select_option(char const* const select)
{
	if (strcmp(select, options[ALL]) == 0) {
		print_all_ctype();
		return ALL;
	}

	/* find and print ctype */
	
	enum select ctype = BOOL;

	for (; ctype < UNKNOWN; ++ctype) {
		if (0 == strcmp(select, options[ctype])) {
			print_ctype(ctype);
			break;
		}
	}

	if (ctype == UNKNOWN) {
		fprintf(stderr, "Unknown option: %s\n", select);
		print_help();
	}

	return ctype;
}

int main(int argc, char* argv[])
{
	printf("\n%s v.%s\n\n", APP_NAME, APP_VER);

	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}

	char const* const select = argv[1];

	enum select const ctype = print_select_option(select);

	return (ctype == UNKNOWN) ? EXIT_FAILURE : EXIT_SUCCESS;
}

