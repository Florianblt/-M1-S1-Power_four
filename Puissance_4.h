//
// Created by Florian Blot on 09/12/2017.
//

#ifndef PUISSANCE_4_IA_PUISSANCE_4_H
#define PUISSANCE_4_IA_PUISSANCE_4_H


#include <string>

class Puissance_4 {

private:
    int nombreJoueurs;
    int joueurActuel;
    bool partieTermine;

    int grille[7][6];
    int colonnesCoups[7];

    bool testVictoire (int player, int col, int row);
    bool testDirection (int player, int col, int row, int moveCol, int moveRow);

public:
    Puissance_4 (int numPlayers = 2);
    void reset ();
    int getEtatCase (int col, int row);
    int getJoueurActuel ();
    int getVainqueur ();
    bool getPartieTermine ();
    void jouerCoup (int player, int col);

};



#endif //PUISSANCE_4_IA_PUISSANCE_4_H
