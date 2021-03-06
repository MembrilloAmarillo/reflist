#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

int     my_strcmp( const char*, const char* );
void  	my_strcpy( char*, char const* );
size_t  my_strlen( char const* );
void 	read_substring( char const*, int*, char*, const char& );
void 	remap_string( char* str, size_t new_len ); 

#endif 
