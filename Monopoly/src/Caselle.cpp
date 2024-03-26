//Ferraro Simone

#include "Caselle.h"

Caselle::Caselle(void){
	this->nome = "";
	this->categoria = ' ';
	this->type = ' ';
	this->status = false;
	this->posizione = -1;
	this->edifici = 'T';
	this->playerName = "";
	this->actPlayer = "";
}

Caselle::Caselle(char type){
	this->nome = "";
	this->categoria = ' ';
	this->type = type;
	this->status = false;
	this->posizione = -1;
	this->edifici = 'T';
	this->playerName = "";
	this->actPlayer = "";
}

Caselle::Caselle(char type, int pos){
	this->nome = "";
	this->categoria = ' ';
	this->type = type;
	this->status = false;
	this->posizione = pos;
	this->edifici = 'T';
	this->playerName = "";
	this->actPlayer = "";
}

Caselle::Caselle(char cat, char type, int pos, std::string nome){
	this->nome = nome;
	this->categoria = cat;
	this->type = type;
	this->status = false;
	this->posizione = pos;
	this->edifici = 'T';
	this->playerName = "";
	this->actPlayer = "";
}

std::string Caselle::getNome(void){
	return this->nome;
}

std::string Caselle::getActPlayer(void){
	return this->actPlayer;
}

char Caselle::getCategoria(void){
	return this->categoria;
}

char Caselle::getType(void){
	return this->type;
}

bool Caselle::getStatus(void){
	return this->status;
}

int Caselle::getPosizione(void){
	return this->posizione;
}

char Caselle::getEdifici(void){
	return this->edifici;
}

std::string Caselle::getPlayerName(void){
	return this->playerName;
}

void Caselle::setNome(std::string nome){
	this->nome = nome;
}

void Caselle::setActPlayer(std::string nome){
	this->actPlayer = nome;
}

void Caselle::setCategoria(char categoria){
	this->categoria = categoria;
}

void Caselle::setType(char type){
	this->type = type;
}

void Caselle::setStatus(bool status){
	this->status = status;
}

void Caselle::setPosizione(int posizione){
	this->posizione = posizione;
}

void Caselle::setEdifici(char edificio){
	this->edifici = edificio;
}

void Caselle::setPlayerName(std::string playerName){
	this->playerName = playerName;
}

Caselle& Caselle::operator=(const Caselle& other) {
    this->nome = other.nome;
    this->actPlayer = other.actPlayer;
    this->categoria = other.categoria;
    this->type = other.type;
    this->status = other.status;
    this->posizione = other.posizione;
    this->edifici = other.edifici;
    this->playerName = other.playerName;
    return *this;
}

bool Caselle::operator==(Caselle cas){
	return (this->nome == cas.nome && this->categoria == cas.categoria && this->posizione == cas.posizione);
}

std::string Caselle::toString(void){
	std::string str = "Player name: " + this->getPlayerName() + "Posizione: " + std::to_string(this->getPosizione())+ 
	" Categoria: "+this->getCategoria() + " ACtualPlayer: "+ this->getActPlayer();
	return str;
}
