#include <iostream>
#include <string>
#include <sstream>

#ifndef CONNECT_4
#define CONNECT_4
#include "Puissance_4.h"
#include "Commandes.h"

#endif

std::string Commandes::getInputText () {

    char input[256];

    scanf("%256s", input);

    return std::string(input);

}


void Commandes::printGameState (Puissance_4 *game) {

    printf("\n-----------------\n");

    for (int row = 5; row >= 0; row--) {

        printf("| ");

        for (int col = 0; col < 7; col++) {

            int player = game->getEtatCase(col, row);
            std::string boardChar;

            if (player == 0) {
                boardChar = " ";
            } else {

                std::stringstream ss;
                ss << player;
                boardChar = ss.str();

            }

            printf("%s ", boardChar.c_str());
        }

        printf("|\n");

    }

    printf("-----------------\n");
    printf("  1 2 3 4 5 6 7  \n\n");

}