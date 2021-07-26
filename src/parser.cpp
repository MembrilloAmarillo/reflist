#include <parser.h>

void Parser::parse_buffer()
{
	char buffer[126];

	int i = 0;
	while( *( buffer_file + i ) != '\0' ) {
		char c = *( buffer_file + i ); 

		switch( c ) {
			case '[':
				{
					++i;
					read_substring( buffer_file, &i, buffer, ']' );
					Lexer::cache.push(buffer);
					printf( "%s\n", Lexer::cache.show_top() );
				}break;
			case '-':
				{
					++i;
					read_substring( buffer_file, &i, buffer, ':' );
					Lexer::cache.push(buffer);
					printf( "%s\n", Lexer::cache.show_top() );
				}break;
			case ':':
				{
					++i;
					read_substring( buffer_file, &i, buffer, '\n' );
					Lexer::cache.push(buffer);
					printf( "%s\n", Lexer::cache.show_top() );
				}break;
			default:
				{}break;
		}

		i++;
	}
}

void Parser::insert_subject( char *const  new_subject )
{
	buff_size += my_strlen( new_subject );
	buffer_file = (char *)realloc( buffer_file, buff_size * sizeof( char ) );
	
	std::strcat( buffer_file, new_subject );

	Lexer::cache.push( new_subject );
	printf( "%s\n", cache.show_top() );
}

void Parser::insert_reference( char* const subject, char* const title, char* const url )
{
	pila<char*> tmp_cache;
	char tmp_buff[126];

	bool founded = false;

	while( ( !Lexer::cache.vacia() ) && ( founded == false ) ) {
		my_strcpy( tmp_buff, Lexer::cache.show_top() );
		if ( std::strcmp( subject, tmp_buff ) == 0 ) {
			Lexer::cache.push( title );
			Lexer::cache.push( url   );
			founded = true;
		} else {
			tmp_cache.push( tmp_buff );
			Lexer::cache.pop();
		}
	}

	if ( founded == false ) {
		insert_subject ( subject );
		Lexer::cache.push( title );
		Lexer::cache.push( url   );
	}
	while( !tmp_cache.vacia() ) {
		my_strcpy( tmp_buff,  tmp_cache.show_top() );
		Lexer::cache.push( tmp_buff );
		tmp_cache.pop();
	}
}
