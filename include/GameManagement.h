//Ferraro Simone, Zerbato Antonio, Zorzetto Matteo

#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Human.h"
#include "Computer.h"
#include "Tabellone.h"
#include "Player.h"
#include "Dado.h"

class GameManagement {
	private:
		std::vector<Player*> players;	//vettore contentente tutti i vari giocatori
		Tabellone tabellone;	//tabellone che verrà utilizzato durante la partita
		std::ofstream outFile;	//file di output dove verranno scritti tutti gli eventi della partita
		int countTurni;		//contatore di turni in una partita

		Player* searchByName(std::string);	//dato in input il nome, ritorna il player
		void startGame(Dado);	//funzione che decide l'ordine di partenza
		void refreshTabellone(Caselle);	//refresha il tabellone

	public:
		//costruttori
		GameManagement();
		GameManagement(std::string, const std::string&);

		//metodi getter
		Tabellone getTabellone(void);
		Player* getPlayer(int);
		Caselle& getCasellaByPosition(int);

		bool check(Player*);	//controlla se il giocatore si trova in una casella laterale o angolare
		bool lateral(Player*);	//siamo in una casella laterale e quindi gestiamo tutte le varie casistiche
		void nextCasella(Player*, int);	//setta al giocatore la prossima casella in cui deve andare dopo aver lanciato i dadi
		void printStartOrder(void);		//stampa l'ordine di partenza dei giocatori
		void run(Dado);	//metodo ch gestisce tutto il gioco
		void findWinner(void);	//trova il vincitore
		void show(void);	//mostra tutte le informazioni nel caso in cui il giocatori umano lo richieda
		void printOwners(void);		//stampa tutte le varie proprietà giocatore per giocatore
		void printTabellone(void);	//stampa il tabellone
		void resetCaselle(Player*);	//quando un giocatore viene eliminato tutte le sue caselle vengono liberate e rese di nuovo disponibili
		~GameManagement();
		
		class PlayerNotFound{};;
};

#endif