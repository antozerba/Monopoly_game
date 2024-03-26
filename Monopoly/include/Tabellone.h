//Ferraro Simone

#ifndef TABELLONE_H
#define TABELLONE_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include "Caselle.h"
#include "Player.h"

class Tabellone{

	private:
		const int nCaselleEconomiche = 8;	//indica il numero totale di caselle economiche ammesse
		const int nCaselleStandard = 10;	//indica il numero totale di caaselle standard ammesse
		const int nCaselleLusso = 6;	//indica il numero totale di caselle lussuose ammesse
		std::vector<Caselle> tabellone;	//vettore di caselle che useremo come tabellone
		std::vector<int> casualCategorie;	//vettore di 24 elem che contiene dei numeri che indicano le categorie di ogni cella

	public:
		//costruttori
		Tabellone(void);
		Tabellone& operator=(const Tabellone&);

		//metodi getter & setter
		void setPos(void);
		void setCasella(int, Caselle&);
		std::string getLetter(Caselle);
		std::string getNumber(Caselle);
		Caselle getCasella(int);
		
		int size(void);	//ritorna la size di tabellone

	friend std::ostream& operator<<(std::ostream&, Tabellone&);
};

#endif