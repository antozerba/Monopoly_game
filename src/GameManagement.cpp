//Ferraro Simone, Zerbato Antonio, Zorzetto Matteo

#include "GameManagement.h"

//possiamo anche toglierlo
GameManagement::GameManagement(void){
	this->countTurni = 0;
	this->tabellone = Tabellone();
	//outFile("log.txt");
	for(int i = 0; i < 4; i++){
		players.push_back(new Human(std::to_string(i)));
	}
}

//costruttore con parametri a cui viene passato il parametro fornito da riga di comando (option), e il nome del file i output
GameManagement::GameManagement(std::string option, const std::string& outLog) : outFile(outLog) {
	this->countTurni = 0;
	this->tabellone = Tabellone();	//richiamo il costruttore di default di Tabellone
	//se option = computer
	if(option == "computer" || option == "Computer" || option == "COMPUTER"){
		for(int i = 0; i < 4; i++){
			this->players.push_back(new Computer(std::to_string(i), this->tabellone.getCasella(0), Dado()));	//inserisco nel vettore 4 giocatori Computer
		}
	//altrimenti se option = human 	
	}else if(option == "human" || option == "Human" || option == "HUMAN"){
		//Dado dado;
		std::cout << "Tu sei il giocatore 0" << std::endl;
		players.push_back(new Human(std::to_string(0), this->tabellone.getCasella(0), Dado()));	//aggiungo un giocatore umano
		for(int i = 1; i < 4; i++){
			//Dado dadi;
			this->players.push_back(new Computer(std::to_string(i), this->tabellone.getCasella(0), Dado()));	//e gli altri tre sono computer 
		}
	}else{
		std::cout << "Parametro non riconosciuto!" << std::endl;
	}
}

//dato il nome del giocatore mi ritorna il giocatore, altrimenti lancia l'eccezione
Player* GameManagement::searchByName(std::string name){
	for(int i = 0; i < players.size(); i++){
		if(players[i]->getNome() == name){
			return players[i];
		}
	}
	throw PlayerNotFound();
}

//metodo che decide l'ordine di partenza dei giocatori
void GameManagement::startGame(Dado dado){
	std::vector<std::pair<Player*, int>> giocatoreDado;	//vettore di pair <Giocatore, numero ottenuto con i dadi>
	for(int i = 0; i < players.size(); i++){
		int ranNumb = players[i]->throwNut();	//faccio lanciare a tutti i giocatori il dado, salvandomi il risultato
		std::cout << "Giocatore " << players[i]->getNome() << " ha lanciato i dadi e ha ottenuto: " << ranNumb << std::endl; 	//stampo nel terminale
		this->outFile << "Giocatore " << players[i]->getNome() << " ha lanciato i dadi e ha ottenuto: " << ranNumb << std::endl; 	//scrivo nel file di log
		giocatoreDado.push_back(std::make_pair(players[i], ranNumb));	//inserisco nel vettore dei pair l'accoppiata giocatore, numero ottenuto
	}

	for(int i = 0; i < giocatoreDado.size() - 1; i++){
		if(giocatoreDado[i].second == giocatoreDado[i + 1].second){
			giocatoreDado[i].second = giocatoreDado[i].first->throwNut();
			giocatoreDado[i + 1].second = giocatoreDado[i + 1].first->throwNut();;
		}
	}

	std::sort(giocatoreDado.begin(), giocatoreDado.end(), [](const auto& a, const auto& b){return a.second > b.second;});	//riordino il vettore il base al giocare che ha ottenuto il punteggio più alto
	
	this->players.clear();	//resetto il vettore di Player per poi reinserire i giocatori in base al numero che hanno ottenuto
	for(int i = 0; i < giocatoreDado.size(); i++){
		players.push_back(giocatoreDado[i].first);
	}
}

//controllo che il giocatore si trovi in una casella laterale e in tal caso chiamo il metodo lateral
bool GameManagement::check(Player* player){
	//std::cout << "Sto controllando" << std::endl;
    if(player->getCasella().getType() == 'L'){
        return lateral(player);
    }else{
    	return true;
    }
}

bool GameManagement::lateral(Player* player){
    Caselle actCas = player->getCasella();	//casella in cui il player si trova in questo momento
    refreshTabellone(actCas);
    //se la casella non appartiene a nessuno (attributo status uguale a false)
    if(!actCas.getStatus()){
        if(player->buyTerreno(actCas)){	//chiedo all'utente se vuole comprare il terreno
        	this->outFile << "Il giocatore " << player->getNome() << " ha comprato il terreno sulla casella " << tabellone.getLetter(actCas)  + tabellone.getNumber(actCas) << std::endl;	//registro tutti sul file di log
        }
		refreshTabellone(actCas);	//devo aggiornare la casella nel tabellone
        return true;
    //casella è occupata
    }else{
        //caso in cui la casella sia già di mia proprietà
        if(actCas.getPlayerName() == player->getNome()){
            //se la casella non ha edifici posso costruire una casa
            if(actCas.getEdifici() == 'T'){
                    if(player->buyCasa(actCas)){	//chiedo se vuole costruire una casa	
                    	this->outFile << "Il giocatore " << player->getNome() << " ha costruito una casa sulla casella " << tabellone.getLetter(actCas)  + tabellone.getNumber(actCas) << std::endl;	//scrivo nel file di log
                    }
                    refreshTabellone(actCas);
                    return true;
            //se ha già una casa posso costruire un hotel
            }else if(actCas.getEdifici() == 'C'){
                    if(player->buyHotel(actCas)){
                    	this->outFile << "Il giocatore " << player->getNome() << " ha migliorato una casa in un albergo sulla casella " << tabellone.getLetter(actCas)  + tabellone.getNumber(actCas) << std::endl;	//scrivo nel file di log
                    }
                    refreshTabellone(actCas);
                    return true;
            //se ho già un hotel non faccio nulla
            }else{
                return true;
            }
        //il terreno non è il nostro
        }else{
        	refreshTabellone(actCas);
        	Player* owner = searchByName(actCas.getPlayerName()); 	//proprietario del terreno
            if(actCas.getEdifici() == 'C'){	//se c'e una casa
            	int costo = player->payCasa(actCas);	//salvo il costo del pernottamento
                bool var = player->payPlayer(*owner, costo);	//pago il proprietario della casa
                this->outFile << "Il giocatore " << player->getNome() << " ha pagato " << costo << " al giocatore " << owner->getNome() << " per il pernottamento nella casella " << tabellone.getLetter(actCas)  + tabellone.getNumber(actCas) << std::endl;	//scrivo nel file di log
                return var;
            }else if(actCas.getEdifici() == 'H'){
            	int costo = player->payHotel(actCas);	//salvo il costo del pernottamento
                bool var = player->payPlayer(*owner, costo);	//pago il proprietario dell'albergo
                this->outFile << "Il giocatore " << player->getNome() << " ha pagato " << costo << " al giocatore " << owner->getNome() << " per il pernottamento nella casella " << tabellone.getLetter(actCas)  + tabellone.getNumber(actCas) << std::endl;	//scrivo nel file di log
      			return var;
            }else{
            	return true;
            }
        }
    }
    refreshTabellone(actCas);
}

//ritorna il tabellone
Tabellone GameManagement::getTabellone(void){
	return this->tabellone;
}

//ritorna il giocatore
Player* GameManagement::getPlayer(int index){
	return this->players[index];
}	

//ritorna la casella passatogli la posizione nel tabellone
Caselle& GameManagement::getCasellaByPosition(int pos){
	Caselle newCaSella;
	for(int i = 0; i < this->tabellone.size(); i++){
		if(this->tabellone.getCasella(i).getPosizione() == pos){
			return newCaSella = this->tabellone.getCasella(i);
		}
	}
}

//setta la giocatore la prossima cassella in cui deve andare
void GameManagement::nextCasella(Player* player, int newNumber){
	const int posTotali = 27;	//n di caselle totali
	Caselle newCasella;
	player->getCasella().setActPlayer(" ");	//settiamo l'atrtibuto actPlayer di oldCasella = a nullo
	int actPosition = player->getCasella().getPosizione();	//salvo la posizione attuale del giocatore
	actPosition += newNumber;	//aggiungo il numero ottenuto lanciando i dadi
	if(actPosition > posTotali){	//se actPosition è maggiore di posTotali vuol dire che sono passato per il via
		player->addBudget(1);	//ritiro i 20 fiorini
		this->outFile << "Il giocatore " << player->getNome() << " è passato dal via e ha ritirato 20 fiorini" << std::endl;	//scrivo sul file di log
		actPosition = actPosition - posTotali - 1;	//la nuova poszione del giocatore è data da questa formula
	}
	//refreshTabellone(player->getCasella());
	//Caselle oldCas = getCasellaByPosition(player->getCasella().getPosizione());
	player->getCasella().setActPlayer(" ");
	getCasellaByPosition(player->getCasella().getPosizione()).setActPlayer(" ");
	//refreshTabellone(player->getCasella());
	std::cout << player->getCasella().toString() << std::endl;
	std::cout << getCasellaByPosition(player->getCasella().getPosizione()).toString() << std::endl;
	newCasella = getCasellaByPosition(actPosition);

	newCasella.setActPlayer(player->getNome());	//setto l'attributo actPlayer di newCasella con il nome del giocatore 
	player->setCasella(newCasella);	//setto l'attributo casella di player con newCasella
	this->outFile << "Il giocatore " << player->getNome() << " è arrivato alla casella " << tabellone.getLetter(newCasella) + tabellone.getNumber(newCasella) << std::endl;		//stampo nel file di log
	
	//possiamo richiamare il metodo refreshTabellone
	refreshTabellone(newCasella);
	//refreshTabellone(oldCasella);
	
	/*std::cout << "Vecchia casella: " << oldCasella.toString() << std::endl;
	std::cout << "Nuova casella: " << player->getCasella().toString() << std::endl;
	std::cout << "Nuova casella: " << newCasella.toString() << std::endl;*/
}

//stampa l'ordine di partenza dei giocatori, sia nel terminale che nel file di log
void GameManagement::printStartOrder(void){
	std::cout << "L'ordine di gioco è il seguente: " <<  std::endl;
	this->outFile << "L'ordine di gioco è il seguente: " <<  std::endl;
	for(int i = 0; i < players.size(); i++){
		std::cout << "Giocatore " << players[i]->getNome() << std::endl;
		this->outFile << "Giocatore " << players[i]->getNome() << std::endl;
	}
}

//metodo che gestisce il gioco
void GameManagement::run(Dado dado){
	startGame(dado);
	printStartOrder();
	//ciclo che funziona finchè il numero di giocatori è uguale a 1 oppure finche i turni sono minori di 5000
	while(players.size() != 1 && countTurni < 500){
		countTurni++;
		auto actPlayer = this->players[0];	//estraggo il primo player dal vettore (quello a cui tocca tirare i dadi)
		if(Human* human = dynamic_cast<Human*>(actPlayer)){	//se è un giocatore umano, chiedo se desidera vedere le varie infomazioni relative a tutti i giocatori
            std::cout<<"Desideri visualizzare le informazioni generali? [S/N]" <<std::endl;
            std::string risposta;
            std::cin >> risposta;
            if(risposta == "S"  || risposta == "s")
                show();
            else if(risposta == "n" || risposta == "N")
            	std::cout << "Ok continuiamo" << std::endl;
            else
            	std::cout << "Risposta non valida, continuiamo" << std::endl;
        }

		this->players.erase(players.begin());	//elimino il primo giocatore dal vettore
		int lancioDadi = actPlayer->throwNut();	//lancia i dadi
		std::cout << "Giocatore " << actPlayer->getNome() << " ha tirato i dadi ottenendo un valore di " << lancioDadi << std::endl;
		this->outFile << "Giocatore " << actPlayer->getNome() << " ha tirato i dadi ottenendo un valore di " << lancioDadi << std::endl;	//scrivo sul file di log
		nextCasella(actPlayer, lancioDadi);	//richiamo il metood nextCasella
		std::cout << "Giocatore " << actPlayer->getNome() << " si trovo nella casella " << tabellone.getLetter(actPlayer->getCasella()) + tabellone.getNumber(actPlayer->getCasella()) <<  std::endl;
		if(check(actPlayer)){	//controllo la poszione in cui è tramite il metodo check e gestisco tutte le verie casistiche
			players.push_back(actPlayer);	//se il metood ritorna true reinserisco il player in fondo alla lista
		}else{	//altrimento viene eliminato in quant non ha abbastanza fiorini per pagare il pernottamento
			resetCaselle(actPlayer);
			std::cout << "Il giocatore " << actPlayer->getNome() << " è stato eliminato" << std::endl;
 			this->outFile << "Il giocatore " << actPlayer->getNome() << " è stato eliminato" << std::endl;	//stampo nel file di log
		}	
	}
	findWinner();

}

//trovo chi è il giocatore con più fiorini e quindi di conseguenza il vincitore
void GameManagement::findWinner(void){
	auto winner = players[0];
	for(int i = 0; i < players.size(); i++){
		std::cout << "Il giocatore " << this->players[i]->getNome() << " ha un budget di " << this->players[i]->getBudget() << std::endl;
		this->outFile << "Il giocatore " << this->players[i]->getNome() << " ha un budget di " << this->players[i]->getBudget() << std::endl;
		if(winner->getBudget() < this->players[i]->getBudget()){
			winner = players[i];
		}
	}
	std::cout << "Il giocatore " << winner->getNome() << " ha vinto la partita!" << std::endl;
	this->outFile << "Il giocatore " << winner->getNome() << " ha vinto la partita!" << std::endl;
}

//stampo tutti i possedimenti di un giocatore
void GameManagement::printOwners(void){   
    for(int j = 0; j < this->players.size(); j++){
        std::cout <<"Giocatore " << players[j]->getNome() << ": ";
        for(int i = 0; i < tabellone.size(); i++){
            if(tabellone.getCasella(i).getPlayerName() == players[j]->getNome()){	//se l'attributo player di caselle è uguale al nome del giocatore
            	if(tabellone.getCasella(i).getEdifici() == 'C'){	//e l'attributo edificiio è uguale a C
            		std::cout << " Casa in " << tabellone.getLetter(tabellone.getCasella(i)) + tabellone.getNumber(tabellone.getCasella(i));
            	}else if(tabellone.getCasella(i).getEdifici() == 'H'){	//o uguale a H
            		std::cout << " Albergo in " << tabellone.getLetter(tabellone.getCasella(i)) + tabellone.getNumber(tabellone.getCasella(i));
            	}else{	//atrimenti si tratta di un terreno senza costruzioni
            		std::cout << " " + tabellone.getLetter(tabellone.getCasella(i)) + tabellone.getNumber(tabellone.getCasella(i));
            	}
            }
        }
        std::cout << "" << std::endl;
    }
    return;
}

void GameManagement::printTabellone(void){
	std::cout << this->tabellone << std::endl;
}

void GameManagement::show(void){
	printOwners();
	std::cout << std::endl;
	printTabellone();
}

//semplice ciclo for che aggiorna la casella corruspondente nel tabellone
void GameManagement::refreshTabellone(Caselle actCas){
	for(int i = 0; i < this->tabellone.size(); i++){
        if(actCas.getPosizione() == tabellone.getCasella(i).getPosizione())
            tabellone.setCasella(i, actCas);
    }
}


//viene invocao quando un giocatore viene eliminato
void GameManagement::resetCaselle(Player* player){
	std::cout << "Resetto tute le caselle di " << player->getNome() << std::endl;
	for(int i = 0; i < this->tabellone.size(); i++){
		if(this->tabellone.getCasella(i).getPlayerName()==player->getNome()){	//trovo tutte le caselle che il giocatore possedeva
			Caselle cas (tabellone.getCasella(i).getCategoria(), tabellone.getCasella(i).getType(), tabellone.getCasella(i).getPosizione(), std::string(1, this->tabellone.getCasella(i).getCategoria()));	//creo una nuova casella con le stesse carretterisca di quella di prima
			tabellone.setCasella(i, cas);
			//std::cout <<tabellone << std::endl;
		}
	}
}

class FileNotFoundException : public std::runtime_error {
public:
    FileNotFoundException(const std::string& filename)
        : std::runtime_error("File not found: " + filename) {
    }
};

GameManagement::~GameManagement(){
	for(Player* player : players){
		delete player;
	}
}