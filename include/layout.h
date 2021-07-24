#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <TAD/lista_enla_cab.h>

#include <parser.h>

class Layout : public Parser
{
public:
	Layout() {}

	void map_file();

	void insert_subject( char const* );
	void insert_reference( char const*, char const*, char const* );

	~Layout() {}
protected:

};

#endif
