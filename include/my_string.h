#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#ifdef __linux__

extern "C" {
#define _GNU_SOURCE 1
#include <sys/mman.h>
}

#else
#include <cstring>
#endif

#include <cstdlib>
#include <cstdio>
#include <cassert>

void  	my_strcpy( char*, char const* );
size_t  my_strlen( char const* );
void 	read_substring( char const*, int*, char*, const char& );
void 	remap_string( char* str, size_t old_len, size_t new_len ); 

#endif 
