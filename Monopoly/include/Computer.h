//ZERBATO ANTONIO
#ifndef COMPUTER_H
#define COMPUTER_H
#include "Player.h"
#include "Caselle.h"

//classe derivata da Player
class Computer : public Player{
    private:
        bool checkProb(void);

    public:
        using Player::Player;   //richiama tutti i costruttori di player
        Computer(const Computer&);    //costruttore di copia
        Computer& operator=(const Computer&); //overloading dell'operatore =
        bool buyTerreno(Caselle&) override; //override del metodo della classe astratta Player
        bool buyCasa(Caselle&) override; //override del metodo della classe astratta Player
        bool buyHotel(Caselle&) override; //override del metodo della classe astratta Player
        ~Computer() override; //override del distruttore della classe astratta Player
};
#endif 