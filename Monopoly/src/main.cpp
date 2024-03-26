#include "Human.h"
#include "GameManagement.h"
#include "Dado.h"

std::string charToString(char* arr[]){
	std::string opt = arr[1];
	return opt;
}

int main(int argc, char* argv[]){
	try{
		std::string option = charToString(argv);
		Dado dado;
		std::string outFile = "log.txt";
		GameManagement monopoli(option, outFile);
		Tabellone tab = monopoli.getTabellone();
		std::cout << tab << std::endl;
		monopoli.run(dado);
		tab = monopoli.getTabellone();
		std::cout << tab << std::endl;
		}catch(GameManagement::PlayerNotFound e){
			std::cout << "Il giocatore non è stato trovato" << std::endl;
		}
	return 0;
}


