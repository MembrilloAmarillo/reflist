#include <parser.h>

void Parser::insert_subject( char *const  new_subject,  Lexer::token election )
{

  switch( election ) {
  case token::SUBJECT :
    {
      // 3 more bytes to insert '[' and ']\n'
      size_t sub_len = my_strlen( new_subject );
      /* mremap( addr, old_size, new_size, flags, ...) __THROW */
      remap_string( buffer_file, buff_size * sizeof(char),
		    (buff_size + sub_len +3) * sizeof(char) );

      buff_size +=  sub_len + 3;

      std::strcat( buffer_file, "[" );
      std::strcat( buffer_file, new_subject );
      std::strcat( buffer_file, "]\n" );
    }break;
  case token::TITLE :
    {
      // 2 more bytes to insert '-' and ':'
      size_t sub_len = my_strlen( new_subject );

      remap_string( buffer_file, buff_size * sizeof(char),
		    (buff_size + sub_len + 2) * sizeof(char) );

      buff_size +=  sub_len + 2;
				
      std::strcat( buffer_file, "-" );
      std::strcat( buffer_file, new_subject );
      std::strcat( buffer_file, ":" );
    }break;
  case token::URL :
    {
      // 2 more byte to insert '\t' and '\n'
      size_t sub_len = my_strlen( new_subject );

      remap_string( buffer_file, buff_size * sizeof(char),
		    (buff_size + sub_len + 2) * sizeof(char) );

      buff_size +=  sub_len + 2;

      std::strcat( buffer_file, "\t" );
      std::strcat( buffer_file, new_subject );
      std::strcat( buffer_file, "\n" );
    }break;
  default:
    fprintf( stderr, "Error inserting election\n \t function: Parse::insert_subject()\n" );
    exit( 1 );
    break;
  }
}

void Parser::insert_reference( char* const subject, char* const title, char* const url )
{
  (void)subject;
  (void)title;
  (void)url;
}
