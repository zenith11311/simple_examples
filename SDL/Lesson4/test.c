/**
 * @ File      : test.c
 * @ Brief     : Loading the image
 *
 * @ Author    : caelum
 * @ Purpose   : for SDL library practice...
 * @ Reference : Original code was from Lazy Foo' Productions (2004-2015)
 **/

#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>

#define WINDOW_WIDTH  320
#define WINDOW_HEIGHT 480

#define TRUE  1
#define FALSE 0

/* Key press surfaces constants */
typedef enum key_press_surfaces_e {
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_MAX
} key_press_surface_t;

char filename_g[][256] = {
    "figure/pressed.bmp",
    "figure/up.bmp",
    "figure/down.bmp",
    "figure/left.bmp",
    "figure/right.bmp"
};

/* Starts up SDL and creates window */
int sdl_init();

/* Load media */
int sdl_load_media();

/* free media and shuts down SDL */
void sdl_close();

/* load individual image */
SDL_Surface* sdl_load_surface(char *path);

SDL_Window*  window_g              = NULL;  // Window to be rendered..
SDL_Surface* screen_surface_g      = NULL;  // The surface contained by the window

SDL_Surface* key_pressed_surface_g[KEY_PRESS_MAX] = { NULL, };  // Image correspond to a keypress
SDL_Surface* loaded_surface_g = NULL;                           // Currently displayed image

/* sdl_initialize function */
int 
sdl_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialization failed...\n");
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return FALSE;
    } else {
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
sdl_load_media() 
{
    int i;
    for (i=KEY_PRESS_DEFAULT; i<KEY_PRESS_MAX; ++i) {
        key_pressed_surface_g[i] = sdl_load_surface(filename_g[i]);
        if(key_pressed_surface_g[i] == NULL) {
            printf("[%s:%d]\tFailed to load image %s...\n", __FILE__, __LINE__, filename_g[i]);
            printf("\t\tSDL Error : %s\n", SDL_GetError());
            return FALSE;
        } 
    }

    return TRUE;
}

SDL_Surface*
sdl_load_surface(char *path) 
{
    SDL_Surface *loaded_surface = SDL_LoadBMP(path); // Load image at specified path 

    if(loaded_surface == NULL) {
        printf("[%s:%d]\tFailed to load image %s...\n", __FILE__, __LINE__, path);
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return NULL;
    }
    return loaded_surface;
}


void
sdl_close()
{
    int i;
    /* Free loaded image */
    for (i=KEY_PRESS_DEFAULT; i<KEY_PRESS_MAX; ++i) {
        SDL_FreeSurface(key_pressed_surface_g[i]);
        key_pressed_surface_g[i] = NULL;
    }

    /* Destroy Window */
    SDL_DestroyWindow(window_g);
    window_g = NULL;

    /* Quit SDL Subsystems */
    SDL_Quit();
}

int
main(int argc, char *args[])
{
    int  quit = false;          // main loop flag
    char path[256] = {0x00, };             // path for input media

    SDL_Event e;                // SDL Event handler
    SDL_Rect  stretched_screen; // Rectangle Entity

    if(!sdl_init()) {
		printf( "[%s:%d]\tFailed to initialize!\n", __FILE__, __LINE__ );
        return FALSE;
    }
    
    if (!sdl_load_media()) {
        printf("[%s:%d]\tFailed to load media\n", __FILE__, __LINE__);
        return FALSE;
    }

    /* Application Loop */
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            /* User requests quit */
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        loaded_surface_g = key_pressed_surface_g[KEY_PRESS_UP];
                        break;
                    case SDLK_DOWN:
                        loaded_surface_g = key_pressed_surface_g[KEY_PRESS_DOWN];
                        break;
                    case SDLK_LEFT:
                        loaded_surface_g = key_pressed_surface_g[KEY_PRESS_LEFT];
                        break;
                    case SDLK_RIGHT:
                        loaded_surface_g = key_pressed_surface_g[KEY_PRESS_RIGHT];
                        break;
                    default:
                        loaded_surface_g = key_pressed_surface_g[KEY_PRESS_DEFAULT];
                        break;
                }
            }
        }
        /* Apply the loaded image */
        SDL_BlitSurface(loaded_surface_g, NULL, screen_surface_g, NULL);

        /* Update the surface */
        SDL_UpdateWindowSurface(window_g);
    }

    /* Free resources and close SDL */
    sdl_close();

    return 0;
}
