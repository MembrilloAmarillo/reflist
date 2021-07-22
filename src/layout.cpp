#include <layout.h>
#include <cassert>

void Layout::map_file() 
{
	assert( buffer_file != nullptr );
	assert( buff_size > 0 );

	int i = 0;
	int j = 0;
	bool reading = false;

	char tmp_buffer[256];

	while ( *( buffer_file + i ) != '\0' ) {
		char c = *( buffer_file + i );

		if ( c == '[' ) {
			reading = true;
		}
		/* insert in map the key */
		else if ( c == ']' ) {
			tmp_buffer[j] = c;
			/* ... */
			for ( int k = 0; k <= j; k++ ) tmp_buffer[k] = '\0';
			j = 0;
			reading = false;
		}
		if ( reading ) {
			tmp_buffer[j] = c;
			j++;
		}

		if ( c == '\n' ) {
			reading = true;
			/* ... */
			for ( int k = 0; k <= j; k++ ) tmp_buffer[k] = '\0';
			j = 0;
		}
		else if ( c != ' ' && !reading ) { 
			reading = true; // found the url
		}
		/* insert in layout the title */
		else if ( c == ':' ) {
			tmp_buffer[j] = c;
			/* ... */
			for ( int k = 0; k <= j; k++ ) tmp_buffer[k] = '\0';
			j = 0;
			reading = false;
		}
		/* insert in layout the url */
		i++;
	} 
}
