#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <parser.h>
#include <lexer.h>

int menu();

int main () 
{
	Parser parse_file;

	parse_file.file( const_cast<char*>("src/references.txt"), const_cast<char*>("r+") );

	fseek( parse_file.get_file(), 0, SEEK_END );
	size_t size = (size_t)ftell( parse_file.get_file() );
	parse_file.buffer( size );

	rewind( parse_file.get_file() );

	size_t file_size_read = fread( parse_file.get_buffer(), 1, parse_file.get_size(), parse_file.get_file() );
	if ( file_size_read != parse_file.get_size() ) {
		fprintf( stderr, "Diferent sizes, error readinf file\n" );
		exit(1);
	}

	parse_file.parse_buffer();

	bool not_exit = true;

	char subject[126];
	char title[126];
	char url[126];

	while( not_exit ) {
		int output = menu();
		switch( output ) {
			case 1:
				{
					std::cout << "Subject name: ";
					std::cin >> subject;
					parse_file.insert_subject( subject, Parser::entry::SUBJECT );
				}break;
			case 2:
				{
					std::cout << "Subject name: ";
					std::cin >> subject;
					std::cout << "Title name: ";
					std::cin >> title;
					std::cout << "Url: ";
					std::cin >> url;
					parse_file.insert_reference( subject, title, url );
				}break;
			case 3:
				{}break;
			case 4:
				{}break;
			case 5:
				{
					not_exit = false;
					parse_file.print_cache();
					printf("Exiting...\n");
				}break;
			default:
				{}break;
		};
	}

	parse_file.fileclose();

	return EXIT_SUCCESS;
}

int menu()
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
