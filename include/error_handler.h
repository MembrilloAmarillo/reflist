#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#include <cstdio>
#include <my_string.h>

class Error_Handler {
 public:
  Error_Handler( ) = default;

  void Get_Error( const char* msg ) {
    error_msg = new char[ my_strlen( msg ) ];
    my_strcpy( error_msg, msg );
  }

  char* What() const {
    return error_msg;
  }
  
  ~Error_Handler() { delete[] error_msg; }
 private:
  char* error_msg;
};

#endif /* _ERROR_HANDLER_H_ */
