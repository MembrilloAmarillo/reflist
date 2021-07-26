#include <my_string.h>

void read_substring( char const* buffer, int* i, char *tmp_buffer, const char& delimiter ) 
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

size_t my_strlen( char const* buffer )
{
	size_t i = 0;
	do {
		i++;
	} while ( *(buffer + i) != '\0' );
	return i;
}

void my_strcpy( char* dest, char const* src )
{
	// assert( my_strlen( dest ) >= my_strlen( src ) );

	int i = 0;
	do {
		*(dest + i) = *(src + i);
		i++;
	} while( *(src + i) != '\0' );
	*(dest + i) = '\0';
}
