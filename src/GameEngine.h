#include <SDL/SDL.h>

#include "PioggiaAsteroidi.h"
#include "Navicella.h"
#include "Player.h"


#define WIDTH  650
#define HEIGHT 650

    class GameEngine {
        public:
            //Lo Schermo di gioco.
            SDL_Surface *screen;
            //La navicella.
            Navicella *nave;
            //Gli Asteroidi.
            PioggiaAsteroidi *pioggia;
            //Il giocatore e la sua interfaccia.
            Player *player;           
            
            GameEngine() {        
                
                //Imposto le dimensioni dello schermo.
                int width = 800;
                int height = 800;  
                /*Set 650x650 16-bits video mode SDL_SWSURFACE |*/
                screen = SDL_SetVideoMode (width, height, 32, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF);
                
                if (screen == NULL)
                {
                    printf ("Errore nell'inizializzazione dello schermo: %s\n", SDL_GetError());                  
                    exit (2);
                }
                
                SDL_WM_SetCaption ("Space Crash", NULL);
                
                player = new Player(screen);  
                player->getName(screen);  

                nave = new Navicella(screen);             
				pioggia = new PioggiaAsteroidi(width, height);                     
            }
            
            //Ciclo principale di loop;
            void main_loop() {
                    int done = 0;
                
                    while (!done)
                    {
                        SDL_Event event;
                
                        /* Scorre gli eventi. */
                        while (SDL_PollEvent (&event))
                        {
                            nave->handle_input(event);
                            
                            if( event.type == SDL_QUIT )
                            {                
                                done = true;
                            }                       
                        }
                        /*Check collison.*/
                        if(pioggia->checkCollision(nave->pos)) {
                            player->collision++; 
                           
                            //Piccolo ritardo.
                            SDL_Delay(500);
                            //Crea l'animazione.
                            Explosion _exp(screen);
                            //Cea la posizione dell'esplosione.
                            SDL_Rect offset;
                            offset.x = nave->pos.x*25;
                            offset.y = nave->pos.y*25;
                            //La esegue. 
                            while(!_exp._done) {
                                /* Disegna tutto.*/        
                                draw ();
                                /* Disegna L'esplosione.*/ 
                                _exp.draw(&offset);
                            }
                            //Piccolo ritardo
                            SDL_Delay(500);
                            done = true;
                        }
                        /*Imposta il livello della prossima ondata.*/                        
                        pioggia->levelUp(player->getPoint());
                        /*Aumenta il punteggio se sono usciti asteroidi.*/
                        player->addPoint( pioggia->move() ); 
                        /* Disegna tutto.*/         
                        draw ();
                    }
            }
            //Disegna tutto.
            void draw ()
            {   
                Uint32 color;
                
                /* Make sure everything is displayed on screen */
                SDL_Flip (screen);
                
                /* Create a black background */
                color = SDL_MapRGB (screen->format, 0, 0, 0);
                SDL_FillRect (screen, NULL, color);
                
                //Visualizza la nave.
                nave->draw();
                //L'interfaccia del giocatore.               
                player->draw();
                //La pioggia di meteoriti.                
                pioggia->draw( screen );         
                
                /* Don't run too fast */
                SDL_Delay (1);
            }
    };
