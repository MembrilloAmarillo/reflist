#include <lexer.h>

inline void Lexer::file( char const* path, char* mode )
{

	file_ref = fopen( path, mode );

	if ( file_ref == nullptr ) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}

}

inline void Lexer::buffer( size_t size )
{
	buffer_file = (char*)malloc( size * sizeof( char ) );
	buff_size = size;

	assert( buffer_file != nullptr );
}

inline void Lexer::fileclose()
{ 
	buffree();
	fclose( file_ref ); 
}

void Lexer::print_cache()
{
	Pila<char*> tmp;

	char buff[126] = {0};
	while( !cache.vacia() ) {
		my_strcpy( buff, cache.tope() );
		tmp.push( buff );
		cache.pop();
	}

	while( !tmp.vacia() ) {
		my_strcpy( buff, tmp.tope() );
		cache.push( buff );
		std::cout << buff << std::endl;
		tmp.pop();
	}
}


