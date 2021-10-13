#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL2/SDL.h>

class Display {
public:
    Display() = default;
    void Display_Init();
    void Display_Destroy();
    ~Display() = default;
private:
    SDL_Window *window;
    SDL_Surface *w_surface;
};

#endif