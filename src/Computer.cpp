//ZERBATO ANTONIO
#include "Computer.h"
#include <random>
//metodo per ritornare se un giocatore può comprare
bool Computer::checkProb(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    int numeroCasuale = dist(gen);
    //return (numeroCasuale <= 25);
    return true;
}
//costruttore di copia
Computer::Computer(const Computer& c){
    this->nome = c.nome;
    this->posizione = c.posizione;
    this->budget = c.budget;
    this->casella = c.casella;
    this->dado = c.dado;
}
//overloading dell'operatore =
Computer& Computer::operator=(const Computer& c){
    if(this != &c)
    {
        this->nome = c.nome;
        this->posizione = c.posizione;
        this->budget = c.budget;
        this->casella = c.casella;
        this->dado = c.dado;
    }
    return *this;
}
//metodo per comprare il terreno della casella in cui si trova il giocaotore
bool Computer::buyTerreno(Caselle& cas){
    int costo = 0;
    switch(cas.getCategoria()){
        case('E'):
            costo = 6;
            break;
        case('S'):
            costo = 10;
            break;
        case('L'):
            costo = 20;
            break;
    }
    if(checkProb() && this->budget > costo){
        this->setBudget(this->getBudget() - costo);
        cas.setPlayerName(this->getNome()); //setto il nome del propritetario della casella
        cas.setStatus(true); //indica che la casella è occupata
        std::cout << "Giocatore " << this->getNome() << " ha acquistato il terreno in posizione " << cas.getPosizione() << std::endl;  
        return true;
    }else if(this->getBudget() < costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{
        std::cout << "Giocatore " << this->getNome() << " non ha acquistato il terreno in posizione " << cas.getPosizione() << std::endl;
        return false;
    }
}
//metodo per comprare una casa nella casella in cui si trova il giocatore
bool Computer::buyCasa(Caselle& cas){
    int costo = 0;
    //determino il costo della casa in base alla categoria
    switch(cas.getCategoria()){
        case('E'):
            costo = 3;
            break;
        case('S'):
            costo = 5;
            break;
        case('L'):
            costo = 10;
            break;
    }
    if(checkProb() && this->budget > costo){  //compro se la funzione probabilistica ritorna true e il costo è minore del budget
        this->setBudget(this->getBudget() - costo); 
        cas.setEdifici('C'); //cambio l'attributo per gli edidici della casella
        cas.setNome(cas.getNome() + "*"); //cambio il nome della casella
        std::cout << "Giocatore " << this->getNome() << " ha costruito una casa nel terreno in posizione " << cas.getPosizione() << std::endl;
        return true;
    }else if(this->getBudget() < costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{
        return false;
    }
}
//metodo per comprare un hotel nella casella in cui si trova il giocatore
bool Computer::buyHotel(Caselle& cas){
    int costo = 0;
    //determino il costo dell'hotel in base alla categoria
    switch(cas.getCategoria()){
        case('E'):
            costo = 3;
            break;
        case('S'):
            costo = 5;
            break;
        case('L'):
            costo = 10;
            break;
    }
    if(checkProb() && this-> budget > costo){ //compro se la funzione probabilistica ritorna true e il costo è minore del budget
        this->setBudget(this->getBudget() - costo);
        cas.setEdifici('H'); //cambio l'attributo per gli edidici della casella
        cas.setNome(cas.getCategoria() + "^"); //cambio il nome della casella
        std::cout << "Giocatore " << this->getNome() << " ha costruito un albergo nel terreno in posizione " << cas.getPosizione() << std::endl;
        return true;
    }else if(this->getBudget() <  costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{

        return false;
    }
    
}
//distruttore
Computer::~Computer(){

}
