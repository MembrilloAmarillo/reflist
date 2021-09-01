#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>

#include <TAD/pila_enla.h>
#include <my_string.h>

class Lexer { 
public:
	Lexer(){}

	void file( char const*, char* );

	void buffer( size_t );

	inline FILE*   get_file() 	const { return file_ref;    }
	inline char*   get_buffer() const { return buffer_file; }
	inline size_t  get_size()   const { return buff_size;   }
	inline size_t& get_size()  		  { return buff_size;   }

	void fileclose();
	void print_cache();

	~Lexer() { }

protected:
	FILE* file_ref;
	char* buffer_file;
	size_t buff_size;

	Pila<char*> cache;

	inline void buffree()	{ free( buffer_file );    }
};

#endif
