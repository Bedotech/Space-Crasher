#include <SDL/SDL.h>
#include "Asteroide.h"
#include <vector>


class FilaAsteroidi {
    private:
        int _densita_fila;
        int _length;
        
    public:
        int vel; //Velocità della fila.        
        int Y; //Posizione sullo schermo.      
        
        
        
        std::vector<Asteroide> asteroidi; // Tutti gli asteroidi appartenenti alla fila.
        
        FilaAsteroidi(int velocita, int densita_fila, int length);
        void show(SDL_Surface* screen);
        void move();
        
        void add(Asteroide A); //Add Asteroide for object.
        void add(int x); //Add Asteroide for coordinate.   
        bool checkCollision(SDL_Rect);//Trova Collisioni.
        
};




FilaAsteroidi::FilaAsteroidi(int velocita, int densita_fila, int length) {            
            //Impostazione offest.
            Y = 0;
            //Imposta la velocità.
            vel = velocita;       
            //Lunghezza fila.
            _length = length/25;           
            //Regola gli elementi per fila.
            if(densita_fila  < 0 || densita_fila > _length) _densita_fila = 10;
            else _densita_fila = densita_fila;
            
            int i, x;
            //Crea un vettore  di 25 elementi che tiene conto delle diverse posizioni 
            //già occupate dai meteoriti.
            std::vector<int> posizione(_length, 0);
            for(i = 0; i< _length; i++) posizione[i] = i;
            //Finche non riempie l'array continua a inserire oggetti.
            while(asteroidi.size() < _densita_fila) {
                
                //Assegna all'asteroide la coordinata X in base al valore contenuto in 'posizione'.
                x = rand()%posizione.size();
                Asteroide A(posizione[x]);
                
                //Elimina l'ultimo elemento richiamato.                
                posizione.erase(posizione.begin() + x);                
                
                asteroidi.push_back(A);            
            }
                      
}  

void FilaAsteroidi::add(Asteroide A) {
    int i = 0; 
    
    while(asteroidi[i].pos.x != A.pos.x) i++; 
    
    if( (i+1) == asteroidi.size() ) asteroidi.push_back(A); 
}

void FilaAsteroidi::add(int x) {
    int i = 0; 
    
    while(asteroidi[i].pos.x != x) i++; 
    
    if( (i+1) == asteroidi.size() ) { Asteroide A(x); asteroidi.push_back(A); }
}

void FilaAsteroidi::move() {
    //Muove l'asteroide verso il basso di un pixel;
    Y += vel;
    
    int i; 
    
    for(i=0; i<_densita_fila; i++)
    {       
        asteroidi[i].pos.y = Y;          
    }
}

void FilaAsteroidi::show( SDL_Surface *screen ) {
    //Mostra tutti gli asteroidi.
    int i;    
            
    for(i=0; i<_densita_fila; i++)         
        asteroidi[i].show(screen);  
}
//Trova Collisioni.
bool FilaAsteroidi::checkCollision(SDL_Rect obj) { 
     int i;
     bool collision = false;
     //Per ogni asteroide controlla se vi è collisione.
     for(i = 0; i<asteroidi.size(); i++)  {
            Asteroide A= asteroidi[i];
           collision = (obj.x == A.pos.x);
           if(collision) break;
     }
     
     return collision;
}
   
