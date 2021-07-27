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
	enum entry { SUBJECT, TITLE, URL };

	Parser() {}

	void parse_buffer();

	void insert_subject( char *const, uint8_t );
	void insert_reference( char *const, char *const, char *const );

	~Parser() {}
};

#endif
