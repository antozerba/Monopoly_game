//ZERBATO ANTONIO
#ifndef PLAYER_H
#define PLAYER_H
#include<string>
#include <iostream>
#include "Dado.h"
#include "Caselle.h"

class Player{

    protected:
        std::string nome; //nome giocatore {0,1,2,3,4}
        int posizione; //posizione del giocatore sul tabellone
        int budget; 
        Caselle casella; //casella in cui si trova il giocatore, cambia ad ogni lancio dei dadi
        Dado dado;   
        
        
    public:
        Player ();       //costruttore di default
        Player (std::string);
        Player (std::string, int); //costruttore iniziale
        Player (std::string, Caselle, Dado);
        Player(const Player&) = delete; //costruttore di copia
        Player& operator=(const Player&) = delete; //overload di =

        void setNome(std::string);
        void setPosizione(int);
        void setBudget(double);
        void setCasella(Caselle&);
        std::string getNome(void);
        int getPosizione(void);
        int getBudget(void);
        Caselle& getCasella(void);

        std::string toString();
        int throwNut();     //metodo che lancia il dado
        //virtual void check(bool) = 0;       //metodo che controlla in che tipo di casella sono
        //virtual void lateral() = 0;  //metodo chiamato quanod il Player si trova su una casella laterale;
        void addBudget(int);
        bool payPlayer(Player&, int);
        virtual bool buyTerreno(Caselle&) = 0; //metodo per comprare un casella
        virtual bool buyCasa(Caselle&) = 0; //metodo per costuire una casa 
        virtual bool buyHotel(Caselle&) = 0; //metodo per costruire un hotel
        int payCasa(Caselle&);
        int payHotel(Caselle&);
        virtual ~Player() {};       //distruttore

        class InsufficientBudget{};
};
#endif 