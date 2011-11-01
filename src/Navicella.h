#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Explosion.h"

#define NAVICELLA_FILE "./img/navicella.bmp"
#define EXPLOSION_FILE "./img/explosion.gif"

class Navicella {
    private:
        SDL_Surface *_screen;
        
    public:
        int x, y; //Posizione sullo schermo. 
        SDL_Rect pos;     
        SDL_Surface *navicella;
        
        Navicella(SDL_Surface *screen);
        ~Navicella();
        void handle_input(SDL_Event);
        void draw();
        bool dedectCollision(SDL_Rect obj);               
};

Navicella::Navicella(SDL_Surface *screen) {
            //Impostazione offest.
            pos.x = 11;
            pos.y = 19;               
            
            //Impostazioni schermo.
            _screen = screen;            
            //Impostazione immagine asteroide.
            navicella = IMG_Load( NAVICELLA_FILE ); //Non controllo se la risorsa è caricata corretamente
            SDL_SetColorKey( navicella, SDL_SRCCOLORKEY, SDL_MapRGB( navicella->format, 0xFF, 0, 0xFF )); 
}   

Navicella::~Navicella() {
	if( navicella != NULL ) {
		SDL_FreeSurface( navicella );
	}
}
void Navicella::handle_input(SDL_Event event) {
            //Fai qualcosa per la navicella.
            if( event.type == SDL_KEYDOWN )
            {
                //Adjust the velocity
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_w: pos.y--; break;
                        case SDLK_a: pos.x--; break;
                        case SDLK_s: pos.y++; break;
                        case SDLK_d: pos.x++;; break;
                    }
                    
            }
            //Il limite è lo schermo diviso per 25 più un unità.            
            int limit_x =  (_screen->w/25); 
            //Per l'altezza il limite è più restrittivo per via delle scritte sul basso.
            int limit_y =  (_screen->h/25) -2;
             
            if(pos.x >= limit_x) pos.x = limit_x -1;
            if(pos.y >= limit_y) pos.y = limit_y -1;
            if(pos.x < 0) pos.x = 0;
            if(pos.y < 0) pos.y = 0;
} 

void Navicella::draw() {
    
    
    //Holds offsets
    SDL_Rect offset = pos;

    //Get offsets
    offset.x *= 25;
    offset.x -= 12;
    offset.y *= 25;

    //Blit
    SDL_BlitSurface( navicella, NULL, _screen, &offset ); 
    
} 


