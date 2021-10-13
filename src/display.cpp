#include <display.h>

void Display::Display_Init() {
    SDL_Init( SDL_INIT_VIDEO );
    window = SDL_CreateWindow( "Reflist", 
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            680, 480,
                                            SDL_WINDOW_OPENGL );

    if( window == NULL ) {
        fprintf( stderr, "Error creating SDL window\n" );
        exit(1);
    }

    w_surface = SDL_GetWindowSurface( window );
    if( w_surface == NULL ) {
        fprintf( stderr, "Error creating SDL window surface\n" );
        exit(1);
    }
    SDL_UpdateWindowSurface( window );

    SDL_Delay( 3000 );
}

void Display::Display_Destroy() {
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}