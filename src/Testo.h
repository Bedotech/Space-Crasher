//Questa classe rappresenta del testo che può e deve essere renderizzato.
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#define FONT "./font/infected.ttf"

class Testo {
    private:
         std::string _text; //Testo da renderizzate.
         SDL_Rect _pos; //Posizione in cui renderizzare.
         
         SDL_Color _textColor;
         TTF_Font *_font; //Il font che realizza la scritta.
         
         SDL_Surface *_screen;//Dove viene stampato il testo.
         SDL_Surface *_surface;//La superficie del testo.
    public:
        //Carica la scritta con il font di base.
        Testo(SDL_Surface *screen,std::string text, SDL_Rect pos, SDL_Color textColor) {
            //Impostazione variabili.
            _text = text;
            _pos = pos;
            _textColor = textColor;
            _screen = screen;
            
            //Intialize default font
            _font = TTF_OpenFont( FONT, 38 );               
        }
        
        //Carica il font specificato.
        Testo(SDL_Surface *screen, std::string text, SDL_Rect pos, std::string font_path , SDL_Color textColor) {
            //Impostazione variabili.
            _text = text;
            _pos = pos;
            _textColor = textColor;
            _screen = screen;
            
            //Intialize default font
            _font = TTF_OpenFont( font_path.c_str(), 38 );               
        }

		~Testo() {
			if( _surface != NULL ) {
				SDL_FreeSurface( _surface );	
			}
		}
        //Lettura  e scrittura testo.
        std::string get_text() { return _text; }
        //Reimposta anche il render.
        void set_text ( std::string text ) { 
            //Renderizza il testo.
            _text = text; 
            _surface = TTF_RenderText_Solid( _font, _text.c_str(), _textColor); 
        }
        //Overload operatore. 
        std::string & operator=(std::string text) { _text = text; }
        void operator+=(char a) { _text += a; }
        
        //Funzione che stampa la scritta.
        void draw() {    
            //Stampa.
            SDL_BlitSurface( _surface, NULL, _screen, &_pos );    
        }
        
        
};
