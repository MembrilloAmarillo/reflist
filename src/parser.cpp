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
				size_t sub_len = my_strlen( new_subject );
				/* mremap( addr, old_size, new_size, flags, ...) __THROW */
				buffer_file = (char*)mremap( buffer_file, buff_size, buff_size + sub_len + 3, MREMAP_MAYMOVE | MREMAP_DONTUNMAP );
				buff_size +=  sub_len + 3;

				assert( buffer_file != MAP_FAILED );
				
				std::strcat( buffer_file, "[" );
				std::strcat( buffer_file, new_subject );
				std::strcat( buffer_file, "]\n" );
			}break;
		case entry::TITLE :
			{
				// 2 more bytes to insert '-' and ':'
				size_t sub_len = my_strlen( new_subject );
				buffer_file = (char*)mremap( buffer_file, buff_size, buff_size + sub_len + 2, MREMAP_MAYMOVE | MREMAP_DONTUNMAP );
				buff_size +=  sub_len + 2;

				assert( buffer_file != MAP_FAILED );
				
				std::strcat( buffer_file, "-" );
				std::strcat( buffer_file, new_subject );
				std::strcat( buffer_file, ":" );
			}break;
		case entry::URL :
			{
				// 2 more byte to insert '\t' and '\n'
				size_t sub_len = my_strlen( new_subject );
				buffer_file = (char*)mremap( buffer_file, buff_size, buff_size + sub_len + 2, MREMAP_MAYMOVE | MREMAP_DONTUNMAP);
				buff_size +=  sub_len + 2;

				assert( buffer_file != MAP_FAILED );

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
	Pila<char*> tmp_cache;
	char tmp_buff[126] = {0};

	bool not_founded = true;

	while( ( !Lexer::cache.vacia() ) &&  not_founded ) {
		my_strcpy( tmp_buff, Lexer::cache.tope() );

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
		my_strcpy( tmp_buff,  tmp_cache.tope() );
		Lexer::cache.push( tmp_buff );
		tmp_cache.pop();
	}
}
