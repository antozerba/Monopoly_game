//Ferraro Simone

#include "Tabellone.h"

//cosrtruttore di default
Tabellone::Tabellone(void){
	this->tabellone.push_back(Caselle('A'));	//prima casella angolare (A1);
	for(int i = 1; i < 7; i++){
		this->tabellone.push_back(Caselle('L'));	//caselle della prima linea laterali
	}
	this->tabellone.push_back(Caselle('A'));	//casella in alto a destra (A8);
	for(int j = 8; j < 20; j++){
		this->tabellone.push_back(Caselle('L'));	//caselle laterali (lati verticali del tabellone)
	}
	this->tabellone.push_back(Caselle('A'));	//casella angolare in basso a sinsitra
	for(int k = 21; k < 27; k++){
		this->tabellone.push_back(Caselle('L'));	//caselle laterali ultima riga dl tabellone
	}
	this->tabellone.push_back(Caselle('A'));	//casella angolar in basso a destra

	std::random_device rd;	//inizializza un dispositivo per generare numeri casuali
	std::mt19937 gen(rd());	//genera numeri casuali sulla base dell'algoritmo Mersenne Twister

	for(int i = 0; i < nCaselleEconomiche; i++) this->casualCategorie.push_back(0);	//riempe il vettore casualCategorie con 8 (n di caselle economiche) zeri
	for(int i = 0; i < nCaselleStandard; i++) this->casualCategorie.push_back(1);	//riempe il vettore casualCategorie con 10 (n di caselle standard) uni
	for(int i = 0; i < nCaselleLusso; i++) this->casualCategorie.push_back(2);	//riempe il vettore casualCategorie con 6 (n di caselle lussuose) due

	//funzione della libreria standard che permette di mescolare un intervallo di numeri generati casualmente
	//e come parametri gli passiamo l'inizio, la fine e la varibaile gen che serve per generare la casualità nello shuffle
	std::shuffle(this->casualCategorie.begin(), this->casualCategorie.end(), gen);
	
	//scorro tutto il vettore appena inzializzato e a ogni casella di tipo L assegno una categoria
	for(int i = 0; i < this->tabellone.size(); i++){
		if(this->tabellone[i].getType() == 'L'){
			int nextCat = casualCategorie[i];
			if(nextCat == 0){
				this->tabellone[i].setCategoria('E');
				this->tabellone[i].setNome(std::string(1, this->tabellone[i].getCategoria()));	//trasformo il carattere in stringa e glielo setto come nome alla casella
			}else if(nextCat == 1){
				this->tabellone[i].setCategoria('S');
				this->tabellone[i].setNome(std::string(1, this->tabellone[i].getCategoria()));	//trasformo il carattere in stringa e glielo setto come nome alla casella
			}else{
				this->tabellone[i].setCategoria('L');
				this->tabellone[i].setNome(std::string(1, this->tabellone[i].getCategoria()));	//trasformo il carattere in stringa e glielo setto come nome alla casella
			}
		}
	}
	this->tabellone[0].setCategoria('P');	//la prima casella in alto a destra è la nostra partenza
	this->tabellone[0].setNome(std::string(1, this->tabellone[0].getCategoria()));	//trasformo il carattere in stringa e glielo setto come nome alla casella
	setPos();
}

Tabellone& Tabellone::operator=(const Tabellone& tab){
	this->tabellone = tab.tabellone;
	this->casualCategorie = tab.casualCategorie;
	return *this;
}

//metodo che setta la posizione corretta di ogni casella
void Tabellone::setPos(void){
	int pos = 0;
	this->tabellone[0].setPosizione(pos);
	pos++;
	for(int i = 1; i < 8; i++){
		this->tabellone[i].setPosizione(pos);
		pos++;
	}
	for(int i = 9; i < 20; i  += 2){
		this->tabellone[i].setPosizione(pos++);
	}
	for(int i = 27; i > 19; i--){
		this->tabellone[i].setPosizione(pos);
		pos++;
	}
	for(int i = 18; i > 7; i  -= 2){
		this->tabellone[i].setPosizione(pos++);
	}
}

void Tabellone::setCasella(int index, Caselle& cas){
	this->tabellone[index] = cas;
}

Caselle Tabellone::getCasella(int index){
	Caselle cas = this->tabellone[index];
	return cas;
}

int Tabellone::size(void){
	return tabellone.size();
}

//associa a ogni casella un lettere per identificare la riga
std::string Tabellone::getLetter(Caselle cas){
	int pos = cas.getPosizione();
	if(pos >= 0 && pos <= 7)
		return "A";
	else if(pos == 8 || pos == 27)
		return "B";
	else if(pos == 9 || pos == 26)
		return "C";
	else if(pos == 10 || pos == 25)
		return "D";
	else if(pos == 11 || pos == 24)
		return "E";
	else if(pos == 12 || pos == 23)
		return "F";
	else if(pos == 13 || pos == 22)
		return "G";
	else if(pos >= 14 && pos <= 21)
		return "H";
	else{
		return "Nessuna pos";
	}
}

//associa a ogni casella un numero corrispondente alla colonna
std::string Tabellone::getNumber(Caselle cas){
	int n = cas.getPosizione();
	if(n == 0 || n == 27 || n == 26 || n == 25|| n == 24 || n == 23 || n == 22 || n == 21)
		return "1";
	else if(n == 1 || n == 20)
		return "2";
	else if(n == 2 || n == 19)
		return "3";
	else if(n == 3 || n == 18)
		return "4";
	else if(n == 4 || n == 17)
		return "2";
	else if(n == 5 || n == 16)
		return "6";
	else if(n == 6 || n == 15)
		return "7";
	else if(n >= 7 && n <= 14)
		return "8";
	else 
		return "Nessun numero";
}

//override dell'operatore << che useremo nella stampa
std::ostream& operator<<(std::ostream& output, Tabellone& tab){
	output <<"\n";
    output<< "   ";
    for(int i = 0; i < 8; i++){
        output<< std::setw(8)<< i+1 ;
    }

    output<< "\n";
    output <<"\n";
    output << std::setw(5)<<"A     ";

    for(int i = 0; i < 8; i++){
        output << "|" << std::setw(3) << tab.getCasella(i).getNome() << std::setfill(' ') << std::setw(2) << tab.getCasella(i).getActPlayer() << " |";
    }

    output << std::endl;
    int j=0;

    for(int i = 8; i < 20; i = i + 2){
        output << static_cast<char>('B' + (i-8)/2) << "     "<<"|" << std::setw(3) << tab.getCasella(i).getNome() << std::setfill(' ') << std::setw(2) << tab.getCasella(i).getActPlayer() << " |" << "                                                " << "|" << std::setw(3) << tab.getCasella(i + 1).getNome() << std::setfill(' ') << std::setw(2) << tab.getCasella(i + 1).getActPlayer() << " |" << std::endl;  
    }

    output << std::setw(5)<<"H     ";

    for(int i = 20; i < 28; i++){
        output << "|" << std::setw(3) << tab.getCasella(i).getNome() << std::setfill(' ') << std::setw(2) << tab.getCasella(i).getActPlayer() <<" |";
    }

    output << std::endl;
    return output;
}


