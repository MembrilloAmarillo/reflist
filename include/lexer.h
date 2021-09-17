#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <TAD/lista_enla_cab.h>
#include <my_string.h>

class Lexer { 
public:

  enum token {
    SUBJECT,
    TITLE,
    URL
  };
  
  Lexer(){}

  void file( const char*, const char* );

  void create_buffer( size_t );

  inline FILE*   get_file()   const { return file_ref;    }
  inline char*   get_buffer() const { return buffer_file; }
  inline size_t  get_size()   const { return buff_size;   }
  inline size_t& get_size()  	    { return buff_size;   }

  void scan_buffer();
  
  ~Lexer() { fileclose(); }

protected:
  FILE* file_ref;
  char* buffer_file;
  size_t buff_size;

  struct s_token {
    char* c_token;
    enum token e_token;
  };
  
  Lista<s_token> tokens;

  inline void buffree()
  {
    free( buffer_file );
  }
  void fileclose();
};

#endif
