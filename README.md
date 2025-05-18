# Monopoly Game

## Descrizione progetto
Monopoly Game è una semplice implementazione digitale del famoso gioco da tavolo Monopoly. Il progetto permette al giocatore di sfidarsi con dei bot in una partita virtuale, acquistando proprietà, pagando affitti, e cercando di diventare il giocatore più ricco. Il gioco è sviluppato in C++ e offre un'interfaccia testuale semplice e intuitiva da riga di comando.

## Istruzioni di compilazione e avvio 
Per compilare ed eseguire il gioco, segui questi passaggi:

1. Clona la repository:
```bash
git clone https://github.com/antozerba/Monopoly_game.git
cd Monopoly_game
```
2. Crea la cartella di build
```bash
rm -rf build
mkdir build
cd build
```
3. Builda il progetto con CMake
```bash
cmake ..
```
4. Compila il progetto
```bash
make  
``` 
5. Esegui il progetto
Per far avviaare il gioco ci sono due opzioni:
- Avviarlo in modalità computer 
```bash
./ProgettoFinale Computer
``` 
- Avviarlo in modalità giocatore per sfidare gli altri bot
```bash
./ProgettoFinale Human
```