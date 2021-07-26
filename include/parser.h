#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <lexer.h>
#include <my_string.h>

class Parser : public Lexer
{
public:
	Parser() {}

	void parse_buffer();

	void insert_subject( char *const );
	void insert_reference( char *const, char *const, char *const );

	~Parser() {}
protected:

};

#endif
