#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "GameEngine.h"

#define WIDTH  650
#define HEIGHT 650


int main (int argc, char *argv[])
{
    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        printf ("Couldn't initialize SDL: %s\n", SDL_GetError ());               
        exit (1);
    }
    atexit (SDL_Quit);
     
    //Initialize SDL_ttf 
    if( TTF_Init() == -1 ) { return 0; }  

    GameEngine game;
    game.main_loop();
    
	SDL_Quit();
    return 0;
}



