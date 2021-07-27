#include <parser.h>

void Parser::parse_buffer()
{
	char buffer[126] = {0};

	int i = 0;
	while( *( buffer_file + i ) != '\0' ) {
		char c = *( buffer_file + i ); 

		switch( c ) {
			case '[':
				{
					++i;
					read_substring( buffer_file, &i, buffer, ']' );
					Lexer::cache.push(buffer);
				}break;
			case '-':
				{
					++i;
					read_substring( buffer_file, &i, buffer, ':' );
					Lexer::cache.push(buffer);
				}break;
			case ':':
				{
					++i;
					read_substring( buffer_file, &i, buffer, '\n' );
					Lexer::cache.push(buffer);
				}break;
			default:
				{}break;
		}

		i++;
	}
}

void Parser::insert_subject( char *const  new_subject,  uint8_t election )
{

	switch( election ) {
		case entry::SUBJECT :
			{
			// 3 more bytes to insert '[' and ']\n'
				buff_size += my_strlen( new_subject ) + 3;
				buffer_file = (char *)realloc( buffer_file, buff_size * sizeof( char ) );
				
				std::strcat( buffer_file, "[" );
				std::strcat( buffer_file, new_subject );
				std::strcat( buffer_file, "]\n" );
			}break;
		case entry::TITLE :
			{
				// 2 more bytes to insert '-' and ':'
				buff_size += my_strlen( new_subject ) + 2;
				buffer_file = (char *)realloc( buffer_file, buff_size * sizeof( char ) );
				
				std::strcat( buffer_file, "-" );
				std::strcat( buffer_file, new_subject );
				std::strcat( buffer_file, ":" );
			}break;
		case entry::URL :
			{
				// 2 more byte to insert '\t' and '\n'
				buff_size += my_strlen( new_subject ) + 2;
				buffer_file = (char *)realloc( buffer_file, buff_size * sizeof( char ) );
				
				std::strcat( buffer_file, "\t" );
				std::strcat( buffer_file, new_subject );
				std::strcat( buffer_file, "\n" );
			}break;
		default:
			break;
	}
	Lexer::cache.push( new_subject );
}

void Parser::insert_reference( char* const subject, char* const title, char* const url )
{
	pila<char*> tmp_cache;
	char tmp_buff[126] = {0};

	bool not_founded = true;

	while( ( !Lexer::cache.vacia() ) &&  not_founded ) {
		my_strcpy( tmp_buff, Lexer::cache.show_top() );

		if ( std::strcmp( subject, tmp_buff ) == 0 ) {
			Lexer::cache.push( title );
			insert_subject( title, entry::TITLE );
			Lexer::cache.push( url );
			insert_subject( url, entry::URL );
			not_founded = false;
		} else {
			tmp_cache.push( tmp_buff );
			Lexer::cache.pop();
		}
	}

	if ( not_founded ) {
		insert_subject( subject, entry::SUBJECT );
		insert_subject( title, entry::TITLE );
		insert_subject( url, entry::URL );
		Lexer::cache.push( title );
		Lexer::cache.push( url   );
	}

	while( !tmp_cache.vacia() ) {
		my_strcpy( tmp_buff,  tmp_cache.show_top() );
		Lexer::cache.push( tmp_buff );
		tmp_cache.pop();
	}
}
