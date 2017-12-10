#include <iostream>
#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "Puissance_4.h"
#endif

#include "Commandes.h"


Puissance_4 game(2);
bool wantQuit = false;


int main (int argc, char *argv[]) {

    printf("/t Puissance 4\n");

    while (!wantQuit) {

        Commandes::printGameState(&game);

        int currentPlayer = game.getJoueurActuel();

        printf("Joueur %d, entrez un numero de colonne (Entre 1 et 7) - 0 pour quitter\n", currentPlayer);
        std::string input = Commandes::getInputText();

        if (input.compare("Quitter") == 0) {
            wantQuit = true;
        } else {

            int col = atoi(input.c_str());
            game.jouerCoup(currentPlayer, col);

            if (game.getPartieTermine()) {

                Commandes::printGameState(&game);

                int winner = game.getVainqueur();
                printf("Fin de la partie, le joueur %d a gagné !\n", winner);
                wantQuit = true;

            }

        }

    }

    return 0;

}