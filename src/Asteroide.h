#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define ASTEROIDE_FILE "./img/asteroide.bmp"

class Asteroide {
    public:
        int vel; //Velocità dell'asteroide        
        
        SDL_Rect pos; //Posizione.     
        SDL_Surface *asteroide;
        
        //Asteroide();
        Asteroide(int x);
        void show(SDL_Surface* screen);        
              
};

Asteroide::Asteroide(int x) {           
            //Impostazione posizione e grandezza.
            pos.x = x;
            pos.y = 0;
            
            pos.w = 25;
            pos.h = 25;
             
            vel = 5;           
            //Impostazione immagine asteroide.
            asteroide = IMG_Load( ASTEROIDE_FILE );
            SDL_SetColorKey( asteroide, SDL_SRCCOLORKEY, SDL_MapRGB( asteroide->format, 0xFF, 0, 0xFF )); 
} 

void Asteroide::show( SDL_Surface *screen ) {
    //Holds offsets
    SDL_Rect offset = pos;

    //Get offsets
    offset.x *= 25;    

    //Blit
    SDL_BlitSurface( asteroide, NULL, screen, &offset );
}      



