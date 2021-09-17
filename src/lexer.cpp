#include <lexer.h>

void Lexer::file( char* path )
{
  file_ref.open( path, std::fstream::in | std::fstream::out | std::fstream::app );

  if( !file_ref ) {
    fprintf( stderr, "Error opening file\n" );
    exit( 1 );
  }

  /* Get file size */
  file_ref.seekg( 0, file_ref.end );
  size_t size = (size_t)file_ref.tellg();
  file_ref.seekg( 0, file_ref.beg );

  create_buffer( size );
  
  /* Get the buffer */
  file_ref.read( buffer_file, static_cast<long>(size) );
  
  /* Check for errors */
  if ( !file_ref ) {
    fprintf( stderr, "lexer.cpp(line 20):\n" );
    fprintf( stderr, "\033[0;31m\tError reading file to buffer\n" );
    fprintf( stderr, "\033[0;37m\tFunction: file_ref.read( buffer_file, static_cast<std::streamsize>(buff_size)\n" );
    file_ref.close();
    exit( 1 );
  }
}

void Lexer::create_buffer( size_t size )
{
  if ( size < 0 ) {
    fprintf( stderr, "lexer.cpp(line 14):\n" );
    fprintf( stderr, "\033[0;31m\tError creating buffer, size = %zu\033[0;37m", size );
    file_ref.close();
    exit( 1 );
  }
  buffer_file = new char[ size ];
  buff_size = size;

  assert( buffer_file != nullptr );
}

void Lexer::fileclose()
{ 
  delete[] buffer_file;
  file_ref.close();
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
