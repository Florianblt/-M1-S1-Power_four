#ifndef PUISSANCE_4_IA_PUISSANCE_4_H
#define PUISSANCE_4_IA_PUISSANCE_4_H


#include <string>
#include <iostream>
#include <array>

class Puissance_4 {

private:
    int nombreJoueurs;
    int joueurActuel;
    bool partieTermine;
    int grille[7][6];
    int colonnesCoups[7];
    int meilleurCoup;

public:
    int totalCoups;
    Puissance_4 (int numPlayers = 2);
    void reset ();
    int getEtatCase (int col, int row);
    int getJoueurActuel ();
    int getVainqueur ();
    bool getPartieTermine ();
    void jouerCoup (int player, int col);
    void ia_jouerCoup(int difficulte, int joueur);
    int tourIA(int grille[7][6], int profondeur, int joueur);
    int eval(int grille [7][6], int joueur, int joueurAdverse);
    int gameResult(int grille[7][6]);
    int negamax(int grille[7][6], int &meilleurcoup,int profondeur, int alpha, int beta, int joueur);
};



#endif //PUISSANCE_4_IA_PUISSANCE_4_H
