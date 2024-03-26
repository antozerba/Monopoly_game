//Ferraro Simone

#ifndef CASELLE_H
#define CASELLE_H
#include <memory>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Caselle{

	private:
		std::string nome;	//serve per la stampa del tabellone, per indicare la "trasformazione" delle varie caselle
		std::string actPlayer;	//identifica il giocatore che si trova momentaneamente sulla casella
		char categoria;	//indica la categoria di ogni casella (Economica, Standard, Lusso)
		char type;	//indica il tipo di casella (Angolare o Laterale)
		bool status;		//specifica se la casella è libera oppure occupata (false = libera, true = occupata)
		int posizione;	//indica la poszione nel tabellone, non uso gli indici del vettore
		char edifici;	//default =  T, se c'è una casa = C, se c'è un hotel = H
		std::string playerName;	//indica il nome del proprieario della casella
		


	public:
		//costruttori
		Caselle(void);
		Caselle(char);
		Caselle(char, int);
		Caselle(char, char, int, std::string);

		//metodi getter & setter
		std::string getNome(void);
		std::string getActPlayer(void);
		char getCategoria(void);
		char getType(void);
		bool getStatus(void);
		char getEdifici(void);
		int getPosizione(void);
		std::string getPlayerName(void);
		void setNome(std::string);
		void setActPlayer(std::string);
		void setCategoria(char);
		void setType(char);
		void setStatus(bool);
		void setPosizione(int);
		void setEdifici(char);
		void setPlayerName(std::string);

		//overloading degli operatori
		Caselle& operator=(const Caselle&);
		bool operator==(Caselle);

		std::string toString(void);	//metodo che ritorna u a stringa con le informazioni principali

};

#endif 