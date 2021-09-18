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
  assert( buffer != nullptr );
  size_t i = 0;
  do {
    i++;
  } while ( *(buffer + i) != '\0' );
  return i;
}

void my_strcpy( char* dest, char const* src )
{
  assert( dest != nullptr && src != nullptr );
  
  int i = 0;
  do {
    *(dest + i) = *(src + i);
    i++;
  } while( *(src + i) != '\0' );

  *(dest + i) = '\0';

}

void remap_string( char* str, size_t new_len )
{
  str = (char*)realloc( str, new_len );
  assert( str != nullptr );
}

int my_strcmp( const char* str1, const char* str2 ) {
  int idx = 0;
  bool equal = true;
  do {
    if ( *( str1 + idx ) != '\0' && *( str2 + idx ) == '\0' ) {
      return 1;
    } else if ( *( str1 + idx ) == '\0' && *( str2 + idx ) != '\0' ) {
      return -1;
    } else if ( *( str1 + idx ) == *( str2 + idx ) ) {
      // equal = true;
    } else {
      equal = false;
    }
  } while ( *( str1 + idx ) != '\0' || *( str2 + idx ) != '\0' );

  if ( equal ) {
    return 0;
  } else {
    return -1;
  }
}
