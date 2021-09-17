#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
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

  void file( char* );

  void create_buffer( size_t );

  /* Observer methods */
  inline char* get_buffer() const { return buffer_file; }
  inline int   get_size()   const { return buff_size;   }

  /* Overload of get_size, lvalue */
  inline int&  get_size() 	  { return buff_size;   }

  void scan_buffer();
  
  ~Lexer() { fileclose(); }

protected:
  std::fstream file_ref;
  char* buffer_file;
  int buff_size;

  struct s_token {
    char* c_token;
    enum token e_token;
  };
  
  Lista<s_token> tokens;

  void fileclose();
};

#endif
