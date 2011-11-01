#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define ASTEROIDE_FILE "./img/asteroide.bmp"

SDL_Surface *AsteroidSurface = NULL;

class Asteroide {
	public:
        int vel; //Velocità dell'asteroide        
        
        SDL_Rect pos; //Posizione.     
        SDL_Surface *asteroide;
        
        //Asteroide();
        Asteroide(int x);
		~Asteroide();
		Asteroide(const Asteroide&);
        void show( SDL_Surface* screen );   
		void Error() {}
              
};

Asteroide::Asteroide(int x) {           
            //Impostazione posizione e grandezza.
            pos.x = x;
            pos.y = 0;
            
            pos.w = 25;
            pos.h = 25;
             
            vel = 5;           
            /*Impostazione immagine asteroide.
			if( AsteroidSurface == NULL ) {
				AsteroidSurface = IMG_Load( ASTEROIDE_FILE );
				SDL_SetColorKey( AsteroidSurface, SDL_SRCCOLORKEY, SDL_MapRGB( AsteroidSurface->format, 0xFF, 0, 0xFF ));			
			}*/
			SDL_Surface *tmp = IMG_Load( ASTEROIDE_FILE );
			SDL_SetColorKey( tmp, SDL_SRCCOLORKEY, SDL_MapRGB( tmp->format, 0xFF, 0, 0xFF ));

			asteroide = SDL_DisplayFormat( tmp );
			//SDL_FreeSurface( tmp );          
} 
//Distruttore della classe.
Asteroide::~Asteroide() {
	//Causa crash!
	if( asteroide != NULL ) {
		SDL_FreeSurface( asteroide );
	}
}

Asteroide::Asteroide( const Asteroide &a ) {
	pos = a.pos;
	//Copy image
	asteroide = SDL_DisplayFormat( a.asteroide );
}

void Asteroide::show( SDL_Surface *screen ) {
    //Holds offsets
    SDL_Rect offset = pos;

    //Get offsets
    offset.x *= 25;    

    //Blit
    SDL_BlitSurface( AsteroidSurface, NULL, screen, &offset );
}      



