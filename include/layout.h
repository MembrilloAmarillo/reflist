#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <map>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <parser.h>

class Layout : public Parser
{
public:
	Layout() {}

	void map_file();

	void insert_subject( char* );
	void insert_reference( char*, char* );

	void print_file();

	~Layout() {}
protected:
	struct layout {
		char* title;
		char* url;

		layout( char *t = nullptr, char* u = nullptr ) :
			title( t ), url( u ) 
		{}
	};
	std::multimap<char*, layout> layouts;
};

#endif
