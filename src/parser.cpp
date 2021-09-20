
#include <parser.h>

void Parser::insert_reference( char* const subject, char* const title, char* const url )
{
  s_token st;
  bool subject_found = false;
  auto pos = tokens.first();
  for ( ; pos != tokens.end() && subject_found == false; pos = tokens.next( pos ) ) {
    st = tokens.element( pos );
    if ( my_strcmp( st.c_token, subject ) == 0 ) {
      subject_found = true;
    }
  }

  if ( subject_found ) {
    my_strcpy( st.c_token, title );
    st.e_token = token::TITLE;
    tokens.insert( st, pos );
    pos = tokens.next( pos );

    my_strcpy( st.c_token, url );
    st.e_token = token::URL;
    tokens.insert( st, pos );
    pos = tokens.next( pos );
  } else {
    pos = tokens.end();
    my_strcpy( st.c_token, subject );
    st.e_token = token::SUBJECT;
    tokens.insert( st, pos );

    my_strcpy( st.c_token, title );
    st.e_token = token::TITLE;
    pos = tokens.next( pos );
    tokens.insert( st, pos );
    
    my_strcpy( st.c_token, url );
    st.e_token = token::URL;
    pos = tokens.next( pos );
    tokens.insert( st, pos );
  }  
}

void Parser::dump_file()
{
  auto pos = Lexer::tokens.first();

  Lexer::file_ref.close();
  Lexer::file_ref.open( Lexer::path_file, std::fstream::out | std::fstream::trunc );
  
  for( ; pos != Lexer::tokens.end(); pos = Lexer::tokens.next( pos ) ) {
    char *element = Lexer::tokens.element( pos ).c_token;
    Lexer::token election = Lexer::tokens.element( pos ).e_token;
    size_t size  = my_strlen( element );
    
    switch( election ) {
    case SUBJECT:
      {
        file_ref.put( '[' );
        file_ref.write( element, (long)size );
        file_ref.put( ']' );
        file_ref.put( '\n' );
      } break;
    case TITLE:
      {
        file_ref.put( '-' );
        file_ref.write( element, (long)size );
        file_ref.put( ':' );        
      } break;
    case URL:
      {
        file_ref.write( element, (long)size );
        file_ref.put( '\n' );
      } break;
    default:
      {
        fprintf( stderr, "dump_file(): error getting token\n" );
        exit( 1 );
      } break;
    }
  }
}
