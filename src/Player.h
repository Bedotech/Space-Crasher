#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include "Testo.h"

#define FONT "./font/infected.ttf"

class Player {
      private:
             SDL_Surface *_screen; //lo schermo su cui renderizzare tutto.
             SDL_Surface *s_name; 
             TTF_Font *font;
             //Il testo del nome e del punteggio.
             Testo *_nome, *_punteggio;
            
             int _point; //Punti del giocatore.
      public:
             
             int collision; //Il numero di collisioni del giocatore.
             std::string name; //Nome del Giocatore.
             
             Player(SDL_Surface *screen) {
                    //impostazioni.                    
                    _screen = screen;
                    //Iniziazione point.
                    _point = 0;
                    collision = 0;
                    
                    //Intialize font
                    font = TTF_OpenFont( FONT, 38 );    
                    
                    //Creazione punteggio.
                    SDL_Rect s_message;                    
                    s_message.x = 10; s_message.y = screen->h - 48;
                    SDL_Color textColor = { 255, 0, 0};
                    _punteggio = new Testo(screen,"Punti 0",s_message,textColor);
                    
                    //Creazione Nome.
                    s_message.x = 0; s_message.y =0;
                    _nome = new Testo(screen,"",s_message,textColor);
                              
             }
             
             void getName( SDL_Surface *screen ) {
                bool done = false;               
                 
                SDL_EnableUNICODE( SDL_ENABLE ); 
                SDL_Surface *message; 
                SDL_Surface *s_name; 
                
                SDL_Color textColor = { 255, 0, 0}; 
                message = TTF_RenderText_Solid( font, "Inserisci il Nome", textColor); 
                s_name = TTF_RenderText_Solid( font, name.c_str(), textColor );
                     
             while(!done) {
                    SDL_Rect offset;
                    
                    offset.x = (screen->w/2)-(8*25); 
                    offset.y = (screen->h/2) - 200;
                    //Blit
                    SDL_BlitSurface( message, NULL, screen, &offset );
                    
                    SDL_Rect offset2;
                    
                    offset2.x = (screen->w/2)-(8*25); 
                    offset2.y = (screen->h/2) -171;
                    //Blit
                    SDL_BlitSurface( s_name, NULL, screen, &offset2 );
                    
                    
                    SDL_Event event;
                
                    /* Scorre gli eventi. */
                    while (SDL_PollEvent (&event))
                    {
                    
                        //Se è premuto un tasto della tastiera
                        if( event.type == SDL_KEYDOWN )
                        {
                            //Creo una copia della stringa.
                            std::string temp = name;
                    
                            //Se la stringa non ha raggiunto la massima dimensione
                            if( name.length() <= 16 )
                            {
                                //Se è uno spazio
                                if( event.key.keysym.unicode == (Uint16)' ' )
                                {
                                    //Append the character
                                    name += (char)event.key.keysym.unicode;
                                }
                                //Se è un numero
                                else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                                {
                                    //Append the character
                                    name += (char)event.key.keysym.unicode;
                                }
                                //Se è una lettera maiuscola
                                else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                                {
                                    //Append the character
                                    name += (char)event.key.keysym.unicode;
                                }
                                //Se è una lettera minuscola
                                else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                                {
                                    //Append the character
                                    name += (char)event.key.keysym.unicode;
                                }
                            }                            
                            //Fine controllo carattere premuto.
                    
                            //Se viene premuto il backspace e la stringa non è vuota.
                            if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( name.length() != 0 ) )
                            {
                                //Rimuove un carattere
                                name.erase( name.length() - 1 );
                            }
                            //Se viene premuto invio viene salvato il nome e si esce dal ciclo.
                            if( event.key.keysym.sym == SDLK_RETURN && ( name.length() != 0 ) ) {
                                done = true;    
                            }
                            
                            //Se la stringa non è cambiata
                            if( name != temp )
                            {
                                //Libera la vecchia superficie.
                                SDL_FreeSurface( s_name );
                    
                                //Ridisegna il testo
                                s_name = TTF_RenderText_Solid( font, name.c_str(), textColor );
                            }
                        }
                        //Fine del controllo tastiera.
                    }
                    //fine primo while che scorre tutti gli eventi
                    
                      /* Make sure everything is displayed on screen */
                    SDL_Flip (screen);
                    /* Don't run too fast */
                    SDL_Delay (1);
                }               
                //Fine secondo while che continua finche non finisce.
                _nome->set_text( name );
                SDL_FreeSurface( message ); 
				SDL_FreeSurface( s_name ); 
                SDL_EnableUNICODE( SDL_DISABLE );  
             }
             //Disegna tutta l'interfaccia.
             void draw() {            
                  //Disegna il nome.
                  _nome->draw();
                  //Disegna il punteggio.
                  _punteggio->draw();                  
             }
             
             //Aggiunge i punti e li aggiorna
             void addPoint( int point) {
                    //Aggiunge ai punti correnti tutto il resto.
                    _point += point;
                    //Riempie la stringa dei punti aggiornandola.
                    char x[10];
                    sprintf_s(x,"Point %d",_point);
                    _punteggio->set_text(x);
             }
             //Ritorna il valore dei punti correnti.
             int getPoint() { return _point; }
};
