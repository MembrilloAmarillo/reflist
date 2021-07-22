#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstdio>
#include <cstdlib>

class Parser { 
public:
	Parser();

	inline void file( char const* path, char* mode ) {

		file_ref = fopen( path, mode );

		if ( file_ref == nullptr ) {
			fprintf(stderr, "Error opening file\n");
			exit(1);
		}

	}
	inline void buffer( size_t size ) {
		buffer_file = new char[ size ];
		buff_size = size;

		if ( buffer_file == nullptr ) {
			fprintf(stderr, "Error allocating the buffer_file file\n");
			exit(1);
		}
	}

	inline FILE*  get_file() 	{ return file_ref;  }
	inline size_t get_size() 	{ return buff_size; }
	inline char*  get_buffer() 	{ return buffer_file; }

	inline void fileclose()	{ fclose( file_ref ); }

	~Parser();
protected:
	FILE* file_ref;
	char* buffer_file;
	size_t buff_size;

	inline void buffree()	{ delete[] buffer_file;    }
};

#endif
