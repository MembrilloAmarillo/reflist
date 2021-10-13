#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <cstdio>
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Display {
public:
    Display() = default;
    void Init();
    void Set_Font( const char* );
    void Destroy();
    void Events();
    ~Display() = default;
private:
    SDL_Window*  window;
    SDL_Surface* w_surface;
    TTF_Font*    font;
};

#endif
