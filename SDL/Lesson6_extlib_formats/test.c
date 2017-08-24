/**
 * @ File      : test.c
 * @ Brief     : test code with simple SDL_Init()/SDL_Quit() functions.
 *
 * @ Author    : caelum
 * @ Purpose   : to check whether sdl installation has successfully installed.
 * @ Reference : Original code was from Lazy Foo' Productions (2004-2015)
 **/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define STRETCHED_WIDTH  640
#define STRETCHED_HEIGHT 480

#define TRUE  1
#define FALSE 0


int sdl_init();
void sdl_close();
SDL_Surface* sdl_load_surface(char *path);
int sdl_load_media(char *filepath);


SDL_Window* window_g = NULL; //The window we'll be redering to
SDL_Surface* screen_surface_g = NULL; // The surface contained by the window
SDL_Surface* loaded_surface_g = NULL; // Current displayed image

int main( int argc, char* args[] )
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
        SDL_BlitSurface( loaded_surface_g, NULL, screen_surface_g, NULL );

        /* Update the surface */
        SDL_UpdateWindowSurface( window_g );

    }

    /* Free resources and close SDL */
    sdl_close();

    return 0;
}

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


SDL_Surface*
sdl_load_surface(char *path)
{
    SDL_Surface* optimized_surface = NULL; // Final Optimized image
    SDL_Surface* loaded_surface = IMG_Load(path); // Load image at specified path 

    if(loaded_surface == NULL) {
        printf("[%s:%d]\tFailed to load image %s...\n", __FILE__, __LINE__, path);
        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return NULL;
    } else {
        /* Convert surface to screen format */
        optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface_g->format, 0);
        if(optimized_surface == NULL) {
            printf("[%s:%d]\tFailed to optimize image %s...\n", __FILE__, __LINE__, path);
            printf("\t\tSDL Error : %s\n", SDL_GetError());
            return NULL;
        }
        /* free loaded surface */
        SDL_FreeSurface(loaded_surface);
    }

    return optimized_surface;

}

int
sdl_load_media(char *filepath) 
{
    loaded_surface_g = sdl_load_surface(filepath);
    if(loaded_surface_g == NULL) {
        printf("[%s:%d]\tFailed to load streched image...\n", __FILE__, __LINE__);
//        printf("\t\tSDL Error : %s\n", SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

