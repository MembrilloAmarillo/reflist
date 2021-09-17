#include <lexer.h>

void Lexer::file( const char* path, const char* mode )
{
  file_ref = fopen( path, mode );

  if ( file_ref == nullptr ) {
    fprintf(stderr, "Error opening file\n");
    exit(1);
  }

  /* Get the file */
  fseek( file_ref, 0, SEEK_END );
  size_t size = (size_t)ftell( file_ref );
  create_buffer( size );

  rewind( file_ref );

  /* Get the buffer */
  size_t file_size_read = fread( buffer_file, 1,
				 size, file_ref );

  /* Check for errors */
  if ( file_size_read != size ) {
    fprintf( stderr, "\033[0;31mlexer.cpp(line 21):\n" );
    fprintf( stderr, "\tDiferent sizes, error reading file\n" );
    exit(1);
  }
}

void Lexer::create_buffer( size_t size )
{
  assert( size > 0 );
  buffer_file = (char*)malloc( size * sizeof(char) );
  buff_size = size;

  assert( buffer_file != nullptr );
}

void Lexer::fileclose()
{ 
  buffree();
  fclose( file_ref ); 
}


void Lexer::scan_buffer()
{
  char buffer[126] = {0};
  auto token_pos = tokens.primera();

  int i = 0;
  while( *( buffer_file + i ) != '\0' ) {
    char c = *( buffer_file + i ); 

    switch( c ) {
    case '[':
      {
	++i;
	read_substring( buffer_file, &i, buffer, ']' );
	s_token s_tk { buffer, token::SUBJECT };
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    case '-':
      {
	++i;
	read_substring( buffer_file, &i, buffer, ':' );
	s_token s_tk { buffer, token::TITLE };
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    case ':':
      {
	++i;
	read_substring( buffer_file, &i, buffer, '\n' );
	s_token s_tk{ buffer, token::URL };
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    default:
      {}break;
    }

    i++;
  }
}
