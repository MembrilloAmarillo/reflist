
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
