#ifndef Puissance_44
#define Puissance_44
#include "Puissance_4.h"
#endif

Puissance_4::Puissance_4 (int nombreJoueurs) {
    this->nombreJoueurs = nombreJoueurs;
    this->reset();
}


void Puissance_4::reset () {

    this->joueurActuel = 1;
    this->partieTermine = false;

    std::fill(this->colonnesCoups, this->colonnesCoups + 7, 0);

    for (int i = 0; i < 7; i++) {
        std::fill(this->grille[i], this->grille[i] + 6, 0);
    }

}


int Puissance_4::getEtatCase(int col, int row){
    return this->grille[col][row];
}


int Puissance_4::getJoueurActuel() {
    return this->joueurActuel;
}


bool Puissance_4::getPartieTermine(){
    return this->partieTermine;
}


int Puissance_4::getVainqueur(){

    if (!this->partieTermine) {
        return 0; // Game isn't over yet (TODO: Throw)
    }

    return this->joueurActuel;
}


void Puissance_4::jouerCoup (int joueur, int col) {

    col--;

    if (this->partieTermine) {
        return; // Game is over (TODO: Throw)
    }

    if (joueur > this->joueurActuel) {
        return; // Invalid player (TODO: Throw)
    }

    if (joueur != this->getJoueurActuel()) {
        return; // Not current player (TODO: Throw)
    }

    if (col > 6) {
        return; // Invalid column (TODO: Throw)
    }

    int *row = &this->colonnesCoups[col];

    if (*row >= 6) {
        return; // Already reached the top (TODO: Throw)
    }

    this->grille[col][*row] = joueur;

    bool hasWon = this->testVictoire(joueur, col, *row);

    if (hasWon) {

        this->partieTermine = true;
        return;

    }

    (*row)++;
    this->joueurActuel++;

    if (this->joueurActuel > joueurActuel) {
        this->joueurActuel = 1;
    }

    return;

}


bool Puissance_4::testDirection(int joueur, int col, int row, int colIncr, int rowIncr) {

    if ((col + (3 * colIncr)) < 0 || (row + (3 * rowIncr)) < 0) { // Check bounds
        return false;
    }

    int colPos = col;
    int rowPos = row;

    for (int i = 0; i < 4; i++) {

        if (this->grille[colPos][rowPos] != joueur) {
            return false;
        } else {

            colPos = colPos + colIncr;
            rowPos = rowPos + rowIncr;

        }

    }

    return true;

}


bool Puissance_4::testVictoire(int player, int col, int row) {

    for (int colIncr = -1; colIncr <= 1; colIncr++) {
        for (int rowIncr = -1; rowIncr <= 1; rowIncr++) {

            if (!(colIncr == 0 && rowIncr == 0)) {

                bool hasWon = this->testDirection(player, col, row, colIncr, rowIncr);

                if (hasWon) {
                    return true;
                }

            }

        }
    }

    return false;

}