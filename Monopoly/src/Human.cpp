//ZERBATO ANTONIO
#include "Human.h"

//Human::Human(std::string s, Human& m){} //richiama il costruttore di Player(std::string, )

//costruttore di copia
Human::Human(const Human& h){
    this->nome = h.nome;
    this->posizione = h.posizione;
    this->budget = h.budget;
    this->casella = h.casella;
    this->dado = h.dado;
}
//overloading dell'operatore =
Human& Human::operator=(const Human& h){
    if (this != &h){ 
        this->nome = h.nome;
        this->posizione = h.posizione;
        this->budget = h.budget;
        this->casella = h.casella;
        this->dado = h.dado;
    }
    return *this;
}
//metodo per comprare la casella in cui si trova il giocatore
bool Human::buyTerreno(Caselle& cas){
    int costo = 0;
    std::string risposta;
    //determino il costo della casella in base alla categoria
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
    std::cout << "Vuoi comprare il terreno? [S/N]" << std::endl;
    std::cin >> risposta;
    if(risposta == "S"  || risposta == "s" && this->getBudget() > costo){ //controllo risposta e se il costo è inferiore al budget
        this->setBudget(this->getBudget() - costo); //aggiorno budget
        cas.setPlayerName(this->getNome()); //aggiorno nome proprietario casella
        cas.setStatus(true); //aggiorno lo stato
        return true;
    }else if(this->getBudget() < costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{
        return false;
    }
}
//metodo per comprare la casa in cui si trova il giocatore
bool Human::buyCasa(Caselle& cas){
    int costo = 0;
    std::string risposta;
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
    std::cout << "Vuoi costruire una casa sul  tuo terreno? [S/N]" << std::endl; 
    std::cin >> risposta;
    if(risposta == "S"  || risposta == "s" && this->getBudget() > costo){ //controllo risposta e se il costo è inferiore al budget
        this->setBudget(this->getBudget() - costo); //aggiorno budget giocatore
        cas.setEdifici('C'); //setto attributo edifici
        cas.setNome(cas.getNome() + "*"); //cambio nome casella
        cas.setPlayerName(this->getNome()); //aggiorno nome proprietario casella
        return true;
    }else if(this->getBudget() < costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{
        return false;
    }
}
//metodo per comprare l'hotel in cui si trova il giocatore
bool Human::buyHotel(Caselle& cas){
    int costo = 0;
    std::string risposta;
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
    std::cout << "Vuoi costruire un hotel sul  tuo terreno? [S/N]" << std::endl;
    std::cin >> risposta;
    if(risposta == "S"  || risposta == "s" && this->getBudget() > costo){ //controllo risposta e se il costo è inferiore al budget
        this->setBudget(this->getBudget() - costo); //aggiorno budget giocatore
        cas.setEdifici('H'); //setto attributo edifici
        cas.setNome(std::to_string(cas.getCategoria()) + "^"); //cambio nome casella
        cas.setPlayerName(this->getNome());
        return true;
    }else if(this->getBudget() <  costo){
        std::cout << "Budget insufficente" << std::endl;
        return false;
    }else{
        return false;
    }
}

Human::~Human(){
    
}