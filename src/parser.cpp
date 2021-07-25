#include <parser.h>

static void my_strcpy( char*, char const* );
static int  my_strlen( char const* );
static void read_substring( char const*, int*, char*, const char& );

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
					cache.push(buffer);
				}break;
			case '-':
				{
					++i;
					read_substring( buffer_file, &i, buffer, ':' );
					cache.push(buffer);
				}break;
			case ':':
				{
					++i;
					read_substring( buffer_file, &i, buffer, '\n' );
					cache.push(buffer);
				}break;
			default:
				{}break;
		}

		i++;

	}
}

void Parser::insert_subject( char const* new_subject )
{
	buff_size += my_strlen( new_subject );
	buffer_file = (char *)realloc( buffer_file, buff_size * sizeof( char ) );
	
	std::strcat( buffer_file, new_subject );

	cache.push( new_subject );
}

void Parser::insert_reference( char const* subject, char const* title, char const* url )
{}

static void read_substring( char const* buffer, int* i, char *tmp_buffer, const char& delimiter ) 
{
	int j = 0;

	assert( buffer != nullptr );

	while( ( *( buffer + *i ) != delimiter )  && ( *( buffer + *i ) != '\0' ) ) {

	if ( j >= 126 ) {
			fprintf( stderr, "Error allocating memory, substring too large\n" );
			exit( 1 );
		}

		*(tmp_buffer + j) = *( buffer + *i );

		j++;
		*i = *(i) + 1;
	}

	*i = *(i) - 1;
	assert( j <= 125 ); /* To add the EOF */
	*(tmp_buffer + j) = '\0';
}

static int my_strlen( char const* buffer )
{
	int i = 0;
	do {
		i++;
	} while ( *(buffer + i) != '\0' );
	return i;
}

static void my_strcpy( char* dest, char const* src )
{
	//assert( my_strlen( dest ) >= my_strlen( src ) );

	int i = 0;
	do {
		*(dest + i) = *(src + i);
		i++;
	} while( *(src + i) != '\0' );
	*(dest + i) = '\0';
}
