#include <cstdlib>
#include <cstdio>

#include <parser.h>
#include <lexer.h>

int menu();

int main ( int argc, char **argv ) 
{
	Parser parse_file;

	parse_file.file( const_cast<char*>("src/references.txt"), const_cast<char*>("r+") );

	fseek( parse_file.get_file(), 0, SEEK_END );
	size_t size = ftell( parse_file.get_file() );
	parse_file.buffer( size );

	rewind( parse_file.get_file() );

	size_t file_size_read = fread( parse_file.get_buffer(), 1, parse_file.get_size(), parse_file.get_file() );
	if ( file_size_read != parse_file.get_size() ) {
		fprintf( stderr, "Diferent sizes, error readinf file\n" );
		exit(1);
	}

	parse_file.parse_buffer();

	bool not_exit = true;

	while( not_exit ) {
		int output = menu();
		switch( output ) {
			case 1:
				{
					parse_file.insert_subject( (char const*)"[subject0]" );
				}break;
			case 2:
				{}break;
			case 3:
				{}break;
			case 4:
				{}break;
			case 5:
				{
					printf("Exiting...\n");
					exit(1);
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
	printf("	4. Delte reference\n");
	printf("	5. Exit\n");
	printf("\n");
	printf("Go to(1-5): ");
	scanf("%d", &select);

	return select;
}
