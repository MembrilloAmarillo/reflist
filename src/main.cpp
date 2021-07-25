#include <cstdlib>
#include <cstdio>

#include <parser.h>
#include <lexer.h>

int menu();

int main ( int argc, char **argv ) 
{
	Lexer lexer_file;

	lexer_file.file( const_cast<char*>("src/references.txt"), const_cast<char*>("r+") );

	fseek( lexer_file.get_file(), 0, SEEK_END );
	size_t size = ftell( lexer_file.get_file() );
	lexer_file.buffer( size );

	rewind( lexer_file.get_file() );

	size_t file_size_read = fread( lexer_file.get_buffer(), 1, lexer_file.get_size(), lexer_file.get_file() );
	if ( file_size_read != lexer_file.get_size() ) {
		fprintf( stderr, "Diferent sizes, error readinf file\n" );
		exit(1);
	}

	// lexer_file.map_file();
	printf( "%s\n", lexer_file.get_buffer() );

	bool not_exit = true;

	while( not_exit ) {
		int output = menu();
		switch( output ) {
			case 1:
				{
					//lexer_file.insert_subject( (char const*)"[Ramadan]" );
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

	lexer_file.fileclose();

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
