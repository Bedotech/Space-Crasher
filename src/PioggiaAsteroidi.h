#include <SDL/SDL.h>

#include "FilaAsteroidi.h"
#include <vector>
#include <ctime>


/*Questa classe funziona come un time, può essere stoppata e startata per far proseguire
  il flusso o meno degli asteroidi.
  Ha tre parametri:
        - _velocitaocità, la _velocitaocità degli asteroidi.
        - Densita, quanti asteroidi per linea.
        - Frequenza, la frequenza con cui vengono creati asteroidi.*/
class PioggiaAsteroidi {
    private:
        //Tempo totale del timer.
        int startTicks;        
        int pausedTicks;
        
        //Stato del timer.
        bool paused;
        bool started;
        
        int _velocita; //Velocità.
        int _velocita_per_pixel;
        int _densita; //Densita.
        int _frequenza; //Frequenza.
        
        int _length; //Lunghezza della fila.
        int _height; //Massima altezza asteroidi.
        
        //Creazione Asteroidi Random.
        bool can_make_hell;
    
    public:
             
        std::vector<FilaAsteroidi> asteroidi;
        
        PioggiaAsteroidi(int length, int height);
        void start();
        void stop();
        void pause();
        void unpause();

        //Ritorna il tempo del timer.
        int get_ticks();

        //Controlla lo stato del timer.
        bool is_started();
        bool is_paused();
        //Disegna ogni asteroide.
        void draw(SDL_Surface* screen);
        int move();
        void createAsteroidi();
       
        
        void levelUp(int point);
        
        //Trova collisioni.
        bool checkCollision(SDL_Rect);           
};

PioggiaAsteroidi::PioggiaAsteroidi(int length, int height) {
            //Valori di base per la regolazione.
            levelUp(0);
            
            //Impostazioni variabili 
            _length = length;
            _height = height;
            
            //Creazione prima fila.
            FilaAsteroidi F(_velocita_per_pixel, _densita, _length);
            asteroidi.push_back(F);
            //Variabili timer.
            startTicks = 0;
            pausedTicks = 0;
            //Stati del timer.
            paused = false;
            started = false;
            //Inizializzazione procedura random.
            srand( time(0));
            //L'inferno non si può realizzare subito!
            can_make_hell = false;
            
} 

int PioggiaAsteroidi::move() {
    //Viene esguito ogni qualvolta i tick del timer superino il conteggio
    //della velocità.
    int point = 0;
    
    if(get_ticks() > _velocita) {
        stop();
        
        int i;
        //Muove ogni fila di asteroidi. 
        for(i=0; i<asteroidi.size(); i++) {
            asteroidi[i].move();
            //Se l'asteroide a sorpassato lo schermo noi lo eliminiamo.
            //Ed aumentiamo il punteggio per ogni asteroide passato.
            if(asteroidi[i].Y >= _height) {
                point += asteroidi[i].asteroidi.size();
                asteroidi.erase(asteroidi.begin()+i);                    
            }         
        }
        //Se l'ultima fila ha superato la distanza che deve intercorrere fra le file 
        //ne crea una nuova.
        if(asteroidi[asteroidi.size()-1].Y >= _frequenza) {       
            //Se puoi crea l'inferno.
            if(can_make_hell && (rand()%10 == 9)) {
                //Crea file che sono più veloci o più lente di altre.
                FilaAsteroidi F((rand()%5)+2, (rand()%10)+3, _length);
                asteroidi.push_back(F);
            }
            //Altrimenti lascia perdere.
            else {
                FilaAsteroidi F(_velocita_per_pixel, _densita, _length);
                asteroidi.push_back(F);
            }
        }
        
        start();            
    }
    //Ritorna il numero di asteroidi schivati.
    return point;    
}

void PioggiaAsteroidi::draw(SDL_Surface *screen) {    
    int i;
    
    for(i=0; i<asteroidi.size(); i++) {
            asteroidi[i].show(screen);
    }   
}

void PioggiaAsteroidi::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void PioggiaAsteroidi::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void PioggiaAsteroidi::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void PioggiaAsteroidi::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int PioggiaAsteroidi::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }
    else
    {
        return SDL_GetTicks() - startTicks;
    }  
 
}

bool PioggiaAsteroidi::is_started()
{
    return started;
}

bool PioggiaAsteroidi::is_paused()
{
    return paused;
}

//Trova Collisioni.
bool PioggiaAsteroidi::checkCollision(SDL_Rect obj) { 
     int i;
     bool collision = false;
     //Per ogni asteroide controlla se vi è collisione.
     for(i = 0; i<asteroidi.size(); i++)  {
           FilaAsteroidi A = asteroidi[i];           
           if(obj.y == A.Y/25) return A.checkCollision(obj);
     }
     
     return collision;
}

void PioggiaAsteroidi::levelUp(int point) {
    //point *=10;
    if(point <= 100) {
        _velocita = 25;
        _velocita_per_pixel = 2;
        _densita = 5;
        _frequenza = 80;
    }
    else if(point <= 250) {
        _velocita = 20;
        _velocita_per_pixel = 2;
        _densita = 6;
        _frequenza = 80;
    }
    else if(point <= 700) {
        _velocita = 20;
        _velocita_per_pixel = 3;
        _densita = 5;
        _frequenza = 75;
    }
    else if(point <= 900) {
        _velocita = 18;
        _velocita_per_pixel = 3;
        _densita = 6;
        _frequenza = 75;
    }
    else if(point <= 1200) {
        _velocita = 15;
        _velocita_per_pixel = 4;
        _densita = 6;
        _frequenza = 75;
    }
    else if(point <= 1400) {
        _velocita = 15;
        _velocita_per_pixel = 4;
        _densita = 7;
        _frequenza = 70;
    }
    else if(point <= 1800) {
        _velocita = 15;
        _velocita_per_pixel = 4;
        _densita = 7;
        _frequenza = 70;
    }
    else if(point <= 2300) {
        _velocita = 15;
        _velocita_per_pixel = 5;
        _densita = 8;
        _frequenza = 65;
    }
    else if(point <= 2600) {
        _velocita = 12;
        _velocita_per_pixel = 5;
        _densita = 8;
        _frequenza = 63;
        can_make_hell = true;
    }
}
