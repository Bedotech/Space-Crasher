#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>

//Questa classe è un esplosion ed è un animazione.
//Permette di controllare i singoli frame dell'animazione.
class Explosion {
    private:
        SDL_Surface *_screen;//Dove viene disegnata l'animazione.                
        std::vector<SDL_Surface*> frame; //Tutti i frame dell'animazione.
        
        //Timer che tiene conto degli fps.
        int _timer;
        
    public:
        int current;
        
        //L'animazione è stata eseguita?
        bool _done;
        
        Explosion(SDL_Surface *screen) {
            _screen = screen;
            
            int i;
            //Carica tutti i frame dell'animazione.
            for(i=0; i<7; i++) {
                SDL_Surface *img;
                //Nome del file.
                char file[30];
                sprintf(file,"./img/explosion/000%d.bmp",i);
                //Caricamento del file.
                img = IMG_Load( file );
                SDL_SetColorKey( img, SDL_SRCCOLORKEY, SDL_MapRGB( img->format, 255, 255, 255)); 
                frame.push_back(img);
            }
            //Tempo dell'ultimo tick.
            _timer = SDL_GetTicks();
            //Frame corrente.
            current = 0;
            //L'animazione non è stata eseguita.
            _done = false;
        }
        
        void draw(SDL_Rect *offset) {    
            if(_done) return;
            //Se è passato tot tempo lo disegna altrimenti niente.
            if( (SDL_GetTicks() - _timer) > 100) {
                _timer = SDL_GetTicks();                
                
                current++; 
                if(current >= 6) _done = true; 
                                    
            }
            
            
            //offset->x -= (frame[current]->w/2);
            //offset->y -= (frame[current]->h/2);
            
            //Disegna il frame corrente, nella posizione specificata.
            SDL_BlitSurface( frame[current], NULL, _screen, offset);                      
        }        
};
