#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <parser.h>
#include <lexer.h>

static int menu()
{
  int select;
  /* "blank" screen */
  //printf("\x1b[2J");
  /* goes to the first line of the screen */
  //printf("\x1b[H");
  printf("--REFERENCIAS--\n");
  printf("	1. Introduce subject.\n");
  printf("	2. Introduce reference.\n");
  printf("	3. Delete subject\n");
  printf("	4. Delete reference\n");
  printf("	5. Exit\n");
  printf("\n");
  printf("Go to(1-5): ");
  scanf("%d", &select);

  return select;
}

int main () 
{
  Parser parse_file;

  parse_file.file( const_cast<char*>("src/references.txt") );

  parse_file.scan_buffer();

  bool exit = false;

  char subject[126];
  char title[126];
  char url[126];

  while( !exit ) {
    int output = menu();
    switch( output ) {
    case 1:
      {
	std::cout << "Subject name: ";
	std::cin >> subject;
	//parse_file.insert_subject( subject, Lexer::token::SUBJECT );
      }break;
    case 2:
      {
	std::cout << "Subject name: ";
	std::cin >> subject;
	std::cout << "Title name: ";
	std::cin >> title;
	std::cout << "Url: ";
	std::cin >> url;
	//parse_file.insert_reference( subject, title, url );
      }break;
    case 3:
      {}break;
    case 4:
      {}break;
    case 5:
      {
	exit = true;
	fprintf( stdout, "%s\n" ,parse_file.get_buffer() );
	fprintf( stdout, "Exiting...\n" );
      }break;
    default:
      {}break;
    };
  }

  return EXIT_SUCCESS;
}

