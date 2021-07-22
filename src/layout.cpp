#include <layout.h>
#include <cassert>

static char* read_subject( char*, int* );
static char* read_title  ( char*, int* );
static char* read_url    ( char*, int* );

void Layout::map_file() 
{
	assert( buffer_file != nullptr );
	assert( buff_size > 0 );
	layout tmp_l;

	int i = 0;
	// if 0 -> title, if 1 -> url
	uint8_t t_or_u = 0;

	char *current_subj;

	while ( *( buffer_file + i ) != '\0' ) {
		char c = *( buffer_file + i );

		if ( c == '[' ) {
			current_subj = read_subject( buffer_file + i, &i );
		}
		else if ( c == '\n' && t_or_u == 0 ) {
			tmp_l.title = read_title( buffer_file + i, &i );
			t_or_u++;
		}
		else if ( c == '\n' && t_or_u == 1 ) {
			tmp_l.url = read_url( buffer_file + i, &i );
			t_or_u = 0;
		}
		layouts.insert( std::make_pair( current_subj, tmp_l ) );
		i++;
	} 
}

static char* read_subject( char* buffer, int* i )
{
	char tmp_buffer[126];
	tmp_buffer[0] = '[';
	int j = 1;
	while( *( buffer + *(i) ) != ']' || *( buffer + *(i) ) != '\0' ) {

		if ( j >= 126 ) {
			fprintf( stderr, "Error allocating memory, subject title too large\n" );
			exit( 1 );
		}

		tmp_buffer[j] = *( buffer + *(i) );

		j++;
		*(i)++;
	}
	assert( j < 124 ); /* To add the ] and the EOF */
	tmp_buffer[++j] = ']';
	tmp_buffer[++j] = '\0';

	return tmp_buffer;
}

static char* read_title( char* buffer, int* i ) 
{
	char tmp_buffer[126];

	assert( 0 && "Todo" );

	return tmp_buffer;
}

static char* read_url( char* buffer, int* i ) 
{
	char tmp_buffer[126];
	
	assert( 0 && "Todo" );

	return tmp_buffer;
}
