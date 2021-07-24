#include <layout.h>

void Layout::print_file() 
{
	auto show_node = []( const auto& node, char end = '\n' ) {
		std::cout << node.first << end;
		std::cout << node.second.title << node.second.url << end;
	};

	std::for_each( layouts.cbegin(), layouts.cend(), [&]( const auto& n ) { show_node(n); } );
}

static void read_substring( char*, int&, char*, const char& );

void Layout::map_file() 
{
	assert( buffer_file != nullptr );
	assert( buff_size > 0 );
	layout tmp_l;

	int i = 0;

	char temp_buffer[126];
	char subject[126];

	while ( *( buffer_file + i ) != '\0' ) {
		char c = *( buffer_file + i );

		if ( c == '[' ) {
			++i;
			read_substring( buffer_file + i, i, temp_buffer, ']' );
			strcpy( subject, temp_buffer );
		}
		else if ( c == ']') {
			++i;
			read_substring( buffer_file + i, i, temp_buffer, ':' );
			tmp_l.title = new char[ strlen( temp_buffer ) + 1 ];
			strcpy( tmp_l.title, temp_buffer );
		}
		else if ( c == ':' ) {
			++i;
			read_substring( buffer_file + i, i, temp_buffer, '\n' );
			tmp_l.url = new char[ strlen( temp_buffer ) + 1 ];
			strcpy( tmp_l.url, temp_buffer );
		}
		layouts.insert( std::make_pair( subject, tmp_l ) );
		i++;
	} 
}

static void read_substring( char* buffer, int& i, char tmp_buffer[], const char& delimiter ) 
{
	int j = 0;
	while( *( buffer + i ) != delimiter && *( buffer + i ) != '\0' ) {

		if ( j >= 126 ) {
			fprintf( stderr, "Error allocating memory, substring too large\n" );
			exit( 1 );
		}

		tmp_buffer[j] = *( buffer + i );

		j++;
		i++;
	}

	assert( j < 125 ); /* To add the EOF */
	tmp_buffer[j] = '\0';
}
