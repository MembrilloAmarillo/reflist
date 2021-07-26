#include <lexer.h>

void Lexer::print_cache()
{
	pila<char*> tmp_cache;

	char tmp_buff[126];

	while( !Lexer::cache.vacia() ) {
		my_strcpy( tmp_buff, Lexer::cache.show_top() );
		tmp_cache.push( tmp_buff );
		Lexer::cache.pop();
	}

	while( !tmp_cache.vacia() ) {
		my_strcpy( tmp_buff, tmp_cache.show_top() );
		printf( "%s\n", tmp_buff );
		Lexer::cache.push( tmp_buff );
		tmp_cache.pop();
	}
}
