#include <layout.h>

void Layout::print_file() 
{
	auto show_node = []( const auto& node, char end = '\n' ) {
		std::cout << "[ " << node.first << " ]" << end;
		std::cout << "- " << node.second.title << ": "<< node.second.url << end;
	};

	std::for_each( layouts.cbegin(), layouts.cend(), [&]( const auto& n ) { show_node(n); } );
}

static void my_strcpy( char*, char const* );
static int  my_strlen( char const* );
static void read_substring( char const*, int*, char*, const char& );

void Layout::map_file() 
{
	assert( buffer_file != nullptr );
	assert( buff_size > 0 );
	layout tmp_l;

	int i = 0;

	char temp_buffer[126];
	char subject[126];

	while ( true ) {
		char c = buffer_file[i];

		if ( c == '\0' ) {
			break;
		}
		else if ( c == '[' ) {
			++i;
			read_substring( buffer_file + i, &i, temp_buffer, ']' );
			my_strcpy( subject, temp_buffer );
		}
		else if ( c == '-') {
			++i;
			read_substring( buffer_file + i, &i, temp_buffer, ':' );
			tmp_l.title = new char[ my_strlen( temp_buffer ) ];
			my_strcpy( tmp_l.title, temp_buffer );
		}
		else if ( c == ':' ) {
			++i;
			read_substring( buffer_file + i, &i, temp_buffer, '\n' );
			tmp_l.url = new char[ my_strlen( temp_buffer ) ];
			my_strcpy( tmp_l.url, temp_buffer );
		}
		layouts.insert( std::make_pair( subject, tmp_l ) );
		++i;
	} 
}

static void read_substring( char const* buffer, int* i, char tmp_buffer[], const char& delimiter ) 
{
	int j = 0;

	while( ( *( buffer + *i ) != delimiter )  && ( *( buffer + *i ) != '\0' ) ) {

	if ( j >= 126 ) {
			fprintf( stderr, "Error allocating memory, substring too large\n" );
			exit( 1 );
		}

		tmp_buffer[j] = *( buffer + *i );

		j++;
		*i = *(i) + 1;
	}

	assert( j < 125 ); /* To add the EOF */
	tmp_buffer[++j] = '\0';
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
