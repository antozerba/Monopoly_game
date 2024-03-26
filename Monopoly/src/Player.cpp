//ZERBATO ANTONIO
#include <cstdlib>
#include "Player.h"

//costruttore default
Player::Player(){
    this->nome = "";
    this->posizione = 0;
    this->budget = 50;
    this->casella = Caselle();
    this->dado = Dado();
}
//costruttore con nome del giocatore
Player::Player(std::string nome){
    this->nome = nome;
    this->posizione = 0;
    this->budget = 50;
    this->casella = Caselle();
    this->dado = Dado();

}
/*Player::Player(std::string s, int pos){
    this->nome = s;
    this->posizione = pos;
    this->budget = 100;
    this-> casella = Caselle();
}*/
//costruttore con nome, casella e dado
Player::Player(std::string s, Caselle cas, Dado dado){
    this->nome = s;
    this->posizione = cas.getPosizione();
    this->budget = 100;
    this->casella = cas;
    this->dado = dado;
}

void Player::setNome(std::string name){
    this->nome = name;
}

void Player::setPosizione(int pos){
    this->posizione = pos;
}

void Player::setBudget(double budget){
    this->budget = budget;
}

void Player::setCasella(Caselle& cas){
    this->casella = cas;
    this->posizione = cas.getPosizione();
}

std::string Player::getNome(void){
    return this->nome;
}

int Player::getPosizione(void){
    return this->posizione;
}

int Player::getBudget(){
    return budget;
}

Caselle& Player::getCasella(void){
    return this->casella;
}

void Player::addBudget(int amount){
    this->budget += amount;
}

bool Player::payPlayer(Player& p, int amount){
    if(this->budget < amount){
        return false;
    }else{
        this->budget -= amount;
        p.setBudget(p.getBudget() + amount);
        return true;
    }
    
}

std::string Player::toString(){
    return "Giocatore " + this->nome + " " + std::to_string(this->budget) + " " + std::to_string(this->posizione);
    
}
//metodo per lanciare i dadi
int Player::throwNut(){
    return this->dado.generateRandomNumbers();
}

//metodo per ritornare il costo di soggiornamento una casa
int Player::payCasa(Caselle& cas){
    int costo = 0;
    //setto in costo in base alla categoria
    switch(cas.getCategoria()){
        case('E'):
            costo = 100;
            //costo = 2;
            break;
        case('S'):
            //costo = 4;
            costo = 1000;
            break;
        case('L'):
            //costo = 7;
            costo = 1500;
            break;
    }
    return costo;
}
//metodo per ritornare il costo di soggiornamento di un hotel
int Player::payHotel(Caselle& cas){
    int costo = 0;
    //setto in costo in base alla categoria
    switch(cas.getCategoria()){
        case('E'):
            //costo = 4;
            costo = 234;
            break;
        case('S'):
            //costo = 8;
            costo = 1500;
            break;
        case('L'):
            //costo = 14;
            costo = 23456;
            break;
    }
    return costo;
}