/**
 * @ File      : test.c
 * @ Brief     : Stretching out loaded image
 *
 * @ Author    : caelum
 * @ Purpose   : for SDL library practice...
 * @ Reference : Original code was from Lazy Foo' Productions (2004-2015)
 **/

#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>

#define STRETCHED_WIDTH  640
#define STRETCHED_HEIGHT 480

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
SDL_Surface* stretched_surface_g = NULL;

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
                                    STRETCHED_WIDTH,
                                    STRETCHED_HEIGHT,
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
    stretched_surface_g = sdl_load_surface(filepath);
    if(stretched_surface_g == NULL) {
        printf("[%s:%d]\tFailed to load streched image...\n", __FILE__, __LINE__);
//        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

void
sdl_close()
{
    /* Free loaded image */
    SDL_FreeSurface(stretched_surface_g);
    stretched_surface_g = NULL;

    /* Destroy Window */
    SDL_DestroyWindow(window_g);
    window_g = NULL;

    /* Quit SDL Subsystems */
    SDL_Quit();
}

SDL_Surface*
sdl_load_surface(char *path)
{
    SDL_Surface* optimizedSurface = NULL; // Final Optimized image
    SDL_Surface* loadedSurface = SDL_LoadBMP(path); // Load image at specified path 

    if(loadedSurface == NULL) {
        printf("[%s:%d]\tFailed to load image %s...\n", __FILE__, __LINE__, path);
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return NULL;
    } else {
        /* Convert surface to screen format */
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screen_surface_g->format, 0);
        if(optimizedSurface == NULL) {
            printf("[%s:%d]\tFailed to optimize image %s...\n", __FILE__, __LINE__, path);
            printf("\t\tSDL Error : %s\n", SDL_GetError());
            return NULL;
        }
        /* free loaded surface */
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;

}

int
main(int argc, char *args[])
{
    int  quit = false;          // main loop flag
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

    /* application loop */
    while(!quit) {
        /* Handle events on the queue */
        while(SDL_PollEvent(&e) != 0) {
            /* Check event for quit request  */
            if(e.type == SDL_QUIT)
                quit = true;
        }

        /* Apply the stretched image */
        stretched_screen.x = 0;
        stretched_screen.y = 0;
        stretched_screen.w = STRETCHED_WIDTH;
        stretched_screen.h = STRETCHED_HEIGHT;
        SDL_BlitScaled( stretched_surface_g, NULL, screen_surface_g, &stretched_screen );

        /* Update the surface */
        SDL_UpdateWindowSurface( window_g );

    }

    /* Free resources and close SDL */
    sdl_close();

    return 0;
}
