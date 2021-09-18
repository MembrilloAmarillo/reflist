#include <lexer.h>

void Lexer::file( const char* path )
{
  int f_value;
  try {
    file_ref.open( path, std::fstream::in | std::fstream::out | std::fstream::app );
    file_ref.exceptions( std::ifstream::failbit );
    file_ref >> f_value;
  } catch ( const std::ios_base::failure& fail ) {
    fprintf( stderr, "%s\n" ,fail.what() );
    exit( 1 );
  }

  /* Get file size */
  file_ref.seekg( 0, file_ref.end );
  size_t size = (size_t)file_ref.tellg();
  file_ref.seekg( 0, file_ref.beg );

  create_buffer( size );

  try {
    /* Get the buffer */
    file_ref.read( buffer_file, static_cast<long>(size) );
    file_ref.exceptions( std::ifstream::failbit );
    file_ref >> f_value;
  } catch ( const std::ios_base::failure& fail ) {
    fprintf( stderr, "%s\n" ,fail.what() );
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
  buffer_file = (char*)malloc( size * sizeof(char) );
  buff_size = size;

  assert( buffer_file != nullptr );
}

void Lexer::fileclose()
{ 
  free( buffer_file );
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
	s_token s_tk;
	s_tk.e_token = token::SUBJECT;
	my_strcpy( s_tk.c_token, buffer );
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    case '-':
      {
	++i;
	read_substring( buffer_file, &i, buffer, ':' );
	s_token s_tk;
	s_tk.e_token = token::TITLE;
	my_strcpy( s_tk.c_token, buffer );
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    case ':':
      {
	++i;
	read_substring( buffer_file, &i, buffer, '\n' );
	s_token s_tk;
	s_tk.e_token = token::URL;
	my_strcpy( s_tk.c_token, buffer );
	tokens.insertar( s_tk, token_pos );
	token_pos = tokens.siguiente( token_pos );
      }break;
    default:
      {}break;
    }

    i++;
  }

  print_tokens();
}

void Lexer::print_tokens() const
{
  auto pos = tokens.primera();

  for( ; pos != tokens.fin(); pos = tokens.siguiente( pos ) ) {
    std::cout << "Token: " << tokens.elemento( pos ).c_token << std::endl;
    std::cout << "\t Tipo: " << tokens.elemento( pos ).e_token << std::endl;
  }
}
