//ZERBATO ANTONIO
#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"
#include <string>
#include <algorithm>
class Human: public Player {
    
    public:
        using Player::Player;   //richiama tutti i costruttori di player
        Human(const Human&);    //costruttore di copia
        Human& operator=(const Human&); //overloading dell'operatore =
        bool buyTerreno(Caselle&) override; //override del metodo della classe astratta Player
        bool buyCasa(Caselle&) override; //override del metodo della classe astratta Player
        bool buyHotel(Caselle&) override; //override del metodo della classe astratta Player
        ~Human() override; //override del distruttore della classe astratta Player


};
#endif