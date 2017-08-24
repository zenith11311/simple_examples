/**
 * @ File      : test.c
 * @ Brief     : Loading the image
 *
 * @ Author    : caelum
 * @ Purpose   : for SDL library practice...
 * @ Reference : Original code was from Lazy Foo' Productions (2004-2015)
 **/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 480

#define TRUE  1
#define FALSE 0

/* Starts up SDL and creates window */
int sdl_init();

/* Load media */
int sdl_load_media(char *filepath);

/* free media and shuts down SDL */
void sdl_close();

/* load individual image */
SDL_Surface* sdl_load_surface(char *path);

/* The window we'll be redering to */
SDL_Window* window_g = NULL;

/* The surface contained by the window */
SDL_Surface* screen_surface_g = NULL;

/* Current displayed image */
SDL_Surface* loaded_surface_g = NULL;

/* sdl_initialize function */
int 
sdl_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization failed...\n");
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return FALSE;
    }
    else {
        /* Create Window */
        window_g = SDL_CreateWindow("SDL Tutorial", 
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if(window_g == NULL) {
            printf("[%s:%d]\tFailed to create window...\n", __FILE__, __LINE__);
            printf("\t\tSDL Error : %s\n", SDL_GetError());
            return FALSE;
        } else {
            screen_surface_g = SDL_GetWindowSurface(window_g);
        }
    }
    return TRUE; 
}

int
sdl_load_media(char *filepath) 
{
    loaded_surface_g = SDL_LoadBMP(filepath); // Load image at specified path 

    if(loaded_surface_g == NULL) {
        printf("[%s:%d]\tFailed to load image %s...\n", __FILE__, __LINE__, filepath);
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

void
sdl_close()
{
    /* Free loaded image */
    SDL_FreeSurface(loaded_surface_g);
    loaded_surface_g = NULL;

    /* Destroy Window */
    SDL_DestroyWindow(window_g);
    window_g = NULL;

    /* Quit SDL Subsystems */
    SDL_Quit();
}

int
main(int argc, char *args[])
{
    char path[256] = {0x00, };             // path for input media

    SDL_Event e;                // SDL Event handler
    SDL_Rect  stretched_screen; // Rectangle Entity

    if(argc != 2) {
        printf("Usage : %s [media_path]\n", args[0]);
        return FALSE; 
    }

    if(!sdl_init()) {
		printf( "[%s:%d]\tFailed to initialize!\n", __FILE__, __LINE__ );
        return FALSE;
    }

    strcpy(path, args[1]);
    
    if (!sdl_load_media(path)) {
        printf("[%s:%d]\tFailed to load media\n", __FILE__, __LINE__);
        return FALSE;
    }

    /* Apply the image */
    SDL_BlitSurface(loaded_surface_g, NULL, screen_surface_g, NULL);

    /* Update the surface */
    SDL_UpdateWindowSurface(window_g);

    /* wait 2s */
    SDL_Delay(2000);

    /* Free resources and close SDL */
    sdl_close();

    return 0;
}
