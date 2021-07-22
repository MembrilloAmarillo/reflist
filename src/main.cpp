#include <cstdlib>
#include <cstdio>

#include <parser.h>
#include <layout.h>

int menu();

int main ( int argc, char **argv ) 
{
	Layout parse_file;

	parse_file.file( const_cast<char*>("src/references.txt"), const_cast<char*>("r+") );

	fseek( parse_file.get_file(), 0, SEEK_END );
	size_t size = ftell( parse_file.get_file() );
	parse_file.buffer( size );

	rewind( parse_file.get_file() );

	size_t file_size_read = fread( parse_file.get_buffer(), 1, parse_file.get_size(), parse_file.get_file() );
	if ( file_size_read != parse_file.get_size() ) {
		fprintf( stderr, "Diferente sizes read, error reading file\n" );
		exit(1);
	}

	bool not_exit = true;

	while( not_exit ) {
		int output = menu();
		switch( output ) {
			case 1:
				{}break;
			case 2:
				{}break;
			case 3:
				{}break;
			case 4:
				{}break;
			case 5:
				{}break;
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
	printf("\x1b[2J");
	/* goes to the first line of the screen */
	printf("\x1b[H");
	printf("--REFERENCIAS--\n");
	printf("	1. Introducir materia.\n");
	printf("	2. Introducir referencia.\n");
	printf("	3. Borrar materia\n");
	printf("	4. Borrar referencia\n");
	printf("	5. Salir\n");
	printf("\n");
	printf("Ir a(1-5): ");
	scanf("%d", &select);

	return select;
}
