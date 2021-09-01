#include <lexer.h>

void Lexer::file( char const* path, char* mode )
{

	file_ref = fopen( path, mode );

	if ( file_ref == nullptr ) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}

}

void Lexer::buffer( size_t size )
{
#ifdef __linux__
	buffer_file = (char*)mmap( NULL, size * sizeof(char), PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
#else
	buffer_file = (char*)malloc( size * sizeof(char) );
#endif
	buff_size = size;

	assert( buffer_file != MAP_FAILED );
}

void Lexer::fileclose()
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


