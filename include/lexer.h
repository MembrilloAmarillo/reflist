#ifndef _PARSER_H_
#define _PARSER_H_

#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>

#include <TAD/sentinel_node_linked_list.h>
#include <my_string.h>
// #include <error_handler.h>

class Lexer { 
public:

  enum token {
    SUBJECT,
    TITLE,
    URL
  };
  
  Lexer(){}

  void file( const char* );

  void create_buffer( size_t );

  /* Observer methods */
  inline char* get_buffer()    const { return buffer_file; }
  inline size_t   get_size()   const { return buff_size;   }

  /* Overload of get_size, lvalue */
  inline size_t&  get_size() 	  { return buff_size;   }

  void scan_buffer();
  
  void dump_to_file();
  
  ~Lexer() { fileclose(); }

protected:
  std::fstream file_ref;
  char* path_file;
  char* buffer_file;
  size_t buff_size;

  struct s_token {
    char c_token[126];
    enum token e_token;
  };
  
  List<s_token> tokens;

  void print_tokens() const;
  void fileclose();

};


#endif
