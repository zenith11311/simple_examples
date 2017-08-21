/**
 * @ File      : test.c
 * @ Brief     : test code with simple SDL_Init()/SDL_Quit() functions.
 *
 * @ Author    : caelum
 * @ Purpose   : to check whether sdl installation has successfully installed.
 * @ Reference : Original code was from Lazy Foo' Productions (2004-2015)
 **/

#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Quit SDL
    SDL_Quit();

    return 0;    
}
