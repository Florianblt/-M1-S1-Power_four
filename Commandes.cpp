//
// Created by Florian Blot on 09/12/2017.
//

#include "Commandes.h"

std::string Commandes::getInputText () {

    char input[256];

    scanf("%256s", input);

    return std::string(input);

}

void Commandes::printGameState (Puissance_4 *game) {
    std::cout<<"\n-----------------\n";

    for (int row = 5; row >= 0; row--) {

        printf("| ");

        for (int col = 0; col < 7; col++) {

            int player = game->getEtatCase(col, row);
            std::string boardChar;

            if (player == 0) {
                boardChar = " ";
            } else {
                if(player == 1)
                    boardChar = "X";
                else
                    boardChar = "O";

            }

            printf("%s ", boardChar.c_str());
        }

        printf("|\n");

    }

    printf("-----------------\n");
    printf("  1 2 3 4 5 6 7  \n\n");

}

void Commandes::menu(){
    bool exit = false;
    while(!exit) {
        std::cout<<"\n\n\tChoisissez votre mode de jeu : \n\n-----------------\n";
        for (int i = 0; i < 7; i++) {
            printf("\n");
            switch (i) {
                case 0:
                    std::cout<<"\tJouer à deux joueurs \t\t\t Entrez (1)";
                    break;
                case 1:
                    std::cout<<"\tJouer contre l'IA (Facile) \t\t Entrez (2)";
                    break;
                case 2:
                    std::cout<<"\tJouer contre l'IA (Moyen) \t\t Entrez (3)";
                    break;
                case 3:
                    std::cout<<"\tJouer contre l'IA (Difficile) \t Entrez (4)";
                    break;
                case 4:
                    std::cout<<"\tMode spectateur \t\t\t\t Entrez (5)";
                    break;
                case 5:
                    std::cout<<"\tQuitter \t\t\t\t\t\t Entrez (6)";
                    break;
                default:
                    break;
            }
        }
        printf("\n-----------------\n");
        int input;
        std::cin >> input;
        switch(input){
            case 1 :
                jouerPartie(input);
                break;
            case 2 :
                jouerPartie(2);
                break;
            case 3 :
                jouerPartie(3);
                break;
            case 4 :
                jouerPartie(4);
                break;
            case 5 :jouerPartie(5);
                break;
            case 6 :
                exit = true;
                break;
            default:
                break;
        }

    }
}

void Commandes::jouerPartie(int modeDeJeu){
    Puissance_4 game(2);
    switch (modeDeJeu){
        case 1:
            while (!game.getPartieTermine()) {
                Commandes::printGameState(&game);
                int joueurActuel = game.getJoueurActuel();
                std::cout<<"Joueur "<<joueurActuel<<" entrez un numero de colonne (Entre 1 et 7)\n";
                std::string input = Commandes::getInputText();
                int col = atoi(input.c_str());
                game.jouerCoup(joueurActuel, col);
            }
            break;
        case 2:
            while (!game.getPartieTermine()) {
                Commandes::printGameState(&game);
                int joueurActuel = game.getJoueurActuel();
                if(joueurActuel == 1) {
                    std::cout<<"Joueur "<<joueurActuel<<" entrez un numero de colonne (Entre 1 et 7)\n";
                    std::string input = Commandes::getInputText();
                    int col = atoi(input.c_str());
                    game.jouerCoup(joueurActuel, col);
                }else{
                    std::cout<<"L'ordinateur joue ...\n";
                    sleep(1);
                    game.ia_jouerCoup(1,2);
                }

            }
            break;
        case 3:
            while (!game.getPartieTermine()) {
                Commandes::printGameState(&game);
                int joueurActuel = game.getJoueurActuel();
                if(joueurActuel == 1) {
                    std::cout<<"Joueur "<<joueurActuel<<" entrez un numero de colonne (Entre 1 et 7)\n";
                    std::string input = Commandes::getInputText();
                    int col = atoi(input.c_str());
                    game.jouerCoup(joueurActuel, col);
                }else{
                    std::cout<<"L'ordinateur joue ...\n";
                    game.ia_jouerCoup(2,2);
                }

            }
            break;
        case 4:
            while (!game.getPartieTermine()) {
                Commandes::printGameState(&game);
                int joueurActuel = game.getJoueurActuel();
                if(joueurActuel == 1) {
                    std::cout<<"Joueur "<<joueurActuel<<" entrez un numero de colonne (Entre 1 et 7)\n";
                    std::string input = Commandes::getInputText();
                    int col = atoi(input.c_str());
                    game.jouerCoup(joueurActuel, col);
                }else{
                    std::cout<<"L'ordinateur joue ...\n";
                    game.ia_jouerCoup(3,2);
                }

            }
            break;
        case 5:
            while (!game.getPartieTermine()) {
                Commandes::printGameState(&game);
                int joueurActuel = game.getJoueurActuel();
                if(joueurActuel == 1) {
                    std::cout<<"L'ordinateur 1 joue ...\n";
                    game.ia_jouerCoup(3,1);
                }else{
                    std::cout<<"L'ordinateur 2 joue ...\n";
                    game.ia_jouerCoup(3,2);
                }

            }

        default:
            break;

    }
    Commandes::printGameState(&game);
    int winner = game.getVainqueur();
    if (winner == 3)
        std::cout<<"Fin de la partie, égalité ! \n";
    else
        std::cout<<"Fin de la partie, le joueur "<< winner << " a gagné !\n";
}