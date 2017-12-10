//
// Created by Florian Blot on 09/12/2017.
//

#ifndef PUISSANCE_4_IA_COMMANDES_H
#define PUISSANCE_4_IA_COMMANDES_H


#include <string>
#include "Puissance_4.h"

class Commandes {

public:
    static std::string getInputText ();
    static void printGameState (Puissance_4 *game);

};

#endif //PUISSANCE_4_IA_COMMANDES_H
