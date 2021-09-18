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

  if ( my_strlen( src ) != my_strlen( dest ) ) {
    try {
      delete[] dest;
      dest = new char[ my_strlen( src ) ];
    } catch( ... ) {
      try{
	dest = (char*)realloc( dest, my_strlen( src ) * sizeof( char ) );
      } catch( ... ) {
	fprintf( stderr, "destination char* have different size and cannot be reallocated\n" );
      }
    }
  }
  
  int i = 0;
  do {
    *(dest + i) = *(src + i);
    i++;
  } while( *(src + i) != '\0' );

  *(dest + i) = '\0';

}

void remap_string( char* str, size_t old_len, size_t new_len )
{
  (void)old_len;
  str = (char*)realloc( str, new_len );
  assert( str != NULL );
}
