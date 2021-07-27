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

	inline void file( char const* path, char* mode ) {

		file_ref = fopen( path, mode );

		if ( file_ref == nullptr ) {
			fprintf(stderr, "Error opening file\n");
			exit(1);
		}

	}
	inline void buffer( size_t size ) {
		buffer_file = (char*)malloc( size * sizeof( char ) );
		buff_size = size;

		assert( buffer_file != nullptr );
	}

	inline size_t  get_size()   const { return buff_size;   }
	inline FILE*   get_file() 	const { return file_ref;    }
	inline char*   get_buffer() const { return buffer_file; }

	inline size_t& get_size()  { return buff_size;   }

	inline void fileclose()	{ 
		buffree();
		fclose( file_ref ); 
	}

	void print_cache() {
		pila<char*> tmp;

		char buff[126] = {0};
		while( !cache.vacia() ) {
			my_strcpy( buff, cache.show_top() );
			tmp.push( buff );
			cache.pop();
		}

		while( !tmp.vacia() ) {
			my_strcpy( buff, tmp.show_top() );
			cache.push( buff );
			std::cout << buff << std::endl;
			tmp.pop();
		}
	}
	
	~Lexer() { }

protected:
	FILE* file_ref;
	char* buffer_file;
	size_t buff_size;

	pila<char*> cache;

	inline void buffree()	{ free( buffer_file );    }
};

#endif
