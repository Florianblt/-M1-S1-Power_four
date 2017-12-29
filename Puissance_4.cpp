//
// Created by Florian Blot on 09/12/2017.
//

#include "Puissance_4.h"

Puissance_4::Puissance_4 (int nombreJoueurs) {
    this->nombreJoueurs = nombreJoueurs;
    this->reset();
}

void Puissance_4::reset () {

    this->totalCoups = 0;
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

    return gameResult(grille);
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
    totalCoups ++;
    int hasWon = gameResult(grille);

    if (hasWon > 0) {
        this->partieTermine = true;
        return;
    }

    (*row)++;
    this->joueurActuel++;

    if (this->joueurActuel > nombreJoueurs) {
        this->joueurActuel = 1;
    }
}

void Puissance_4::ia_jouerCoup(int difficulte, int joueur){
    int col;
    switch (difficulte){
        case 1 :
            col = rand() % 7;
            while(colonnesCoups[col] >= 6) {
                col = rand() % 7;
            }
            this->grille[col][colonnesCoups[col]] = joueur;
            if(gameResult(grille) > 0) {
                this->partieTermine = true;
                break;
            }
            colonnesCoups[col] ++;
            this->joueurActuel ++;
            if (this->joueurActuel > nombreJoueurs) {
                this->joueurActuel = 1;
            }
            break;
        case 2:
            col = tourIA(grille,4,2);
            this->grille[col][colonnesCoups[col]] = joueur;
            if(gameResult(grille) > 0) {
                this->partieTermine = true;
                break;
            }
            colonnesCoups[col] ++;
            this->joueurActuel ++;
            if (this->joueurActuel > nombreJoueurs) {
                this->joueurActuel = 1;
            }
            break;
        case 3:
            col = tourIA(grille,8,2);
            this->grille[col][colonnesCoups[col]] = joueur;
            if(gameResult(grille) > 0) {
                this->partieTermine = true;
                break;
            }
            colonnesCoups[col] ++;
            this->joueurActuel ++;
            if (this->joueurActuel > nombreJoueurs) {
                this->joueurActuel = 1;
            }
            break;
        default:
            break;
    }

}

int Puissance_4::negamax(int grille[7][6], int &meilleurCoup, int profondeur, int alpha, int beta, int joueur){
    int meilleurScore = - std::numeric_limits<int>::max();
    int joueurAdverse;
    if(joueur == 1)
        joueurAdverse = 2;
    else
        joueurAdverse = 1;
    if(gameResult(grille) != 0 || profondeur == 0)
        meilleurScore = eval(grille, joueur, joueurAdverse);
    else {
        int score;
        int prochainMeilleurCoup;
        std::array<int, 7> columns = {3, 4, 5, 0, 1, 2, 6};
        std::random_shuffle(columns.begin(), columns.end());


        for (int i : columns) {
            if (colonnesCoups[i] <= 6) {
                if (grille[i][colonnesCoups[i]] == 0) {
                    grille[i][colonnesCoups[i]] = joueur;
                    colonnesCoups[i]++;
                    totalCoups ++;
                    score = -negamax(grille,prochainMeilleurCoup,profondeur - 1, -beta, -alpha, joueurAdverse);
                    colonnesCoups[i]--;
                    grille[i][colonnesCoups[i]] = 0;
                    totalCoups --;
                    if (score > meilleurScore) {
                        meilleurScore = score;
                        meilleurCoup = i;
                    }
                    if(score > alpha){
                        alpha = meilleurScore;
                        meilleurCoup = i;
                        if(alpha > beta){
                            break;
                        }
                    }
                }
            }
        }
    }
    return meilleurScore;
}

int Puissance_4::tourIA(int grille[7][6], int profondeur, int joueur) {
    meilleurCoup = 3;
    int score = negamax(grille,meilleurCoup, profondeur, - std::numeric_limits<int>::max() , std::numeric_limits<int>::max(), joueur);
    std::cout << meilleurCoup << "\n";
    return meilleurCoup;
}

int Puissance_4::eval(int grille[7][6], int joueur, int joueurAdverse) {
    if (gameResult(grille) == joueur)
        return 10000 - totalCoups;
    else if (gameResult(grille) == joueurAdverse)
        return -10000 + totalCoups;
    else{
        //On compte évalue la valeur de la grille actuelle
        int score = 0, cpt = 0, joueurAdverse;
        if(joueur == 1)
            joueurAdverse = 2;
        else
            joueurAdverse = 1;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 6; j++) {
                if (grille[i][j] == 0) continue;
                //Colonnes
                if(j<3){
                    if(grille[i][j] == joueur){
                        ++cpt;
                        while(grille[i][j + cpt] == joueur){
                            ++cpt;
                        }
                        if(grille[i][j + cpt + 1] != joueurAdverse) {
                            if (cpt == 3) {
                                score += 1000;
                            } else if (cpt == 2) {
                                score += 100;
                            } else {
                                score += 10;
                            }
                        }
                        cpt = 0;
                    }else if(grille[i][j] == joueurAdverse){
                        ++cpt;
                        while(grille[i][j + cpt] == joueurAdverse){
                            ++cpt;
                        }
                        if(grille[i][j + cpt + 1] != joueur) {
                            if (cpt == 3) {
                                score -= 1000;
                            } else if (cpt == 2) {
                                score -= 100;
                            } else {
                                score -= 10;
                            }
                        }
                        cpt = 0;
                    }
                }
                //Lignes
                if(i<4){
                    if(grille[i][j] == joueur){
                        ++cpt;
                        while(grille[i + cpt][j] == joueur){
                            ++cpt;
                        }
                        if(i != 0) {
                            if (grille[i + cpt + 1][j] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }else{
                            if (grille[i + cpt + 1][j] != joueurAdverse || grille[i-1][j] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }
                        cpt = 0;
                    }else if(grille[i][j] == joueurAdverse){
                        ++cpt;
                        while(grille[i + cpt][j] == joueurAdverse){
                            ++cpt;
                        }
                        if(i != 0) {
                            if (grille[i + cpt + 1][j] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }else{
                            if (grille[i + cpt + 1][j] != joueur || grille[i-1][j] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }
                        cpt = 0;
                    }
                }
                //verif diagonale vers haut droite
                if(j<3 && i<4){
                    if(grille[i][j] == joueur){
                        ++cpt;
                        while(grille[i + cpt][j + cpt] == joueur){
                            ++cpt;
                        }
                        if(i != 0 && j!=0){
                            if(grille[i + cpt + 1][j + cpt + 1] != joueurAdverse || grille[i-1][j-1] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }else{
                            if(grille[i + cpt + 1][j + cpt + 1] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }
                        cpt = 0;
                    }
                    else if(grille[i][j] == joueurAdverse){
                        ++cpt;
                        while(grille[i + cpt][j + cpt] == joueurAdverse){
                            ++cpt;
                        }
                        if(i != 0 && j!=0){
                            if(grille[i + cpt + 1][j + cpt + 1] != joueur || grille[i-1][j-1] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }else{
                            if(grille[i + cpt + 1][j + cpt + 1] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }
                        cpt = 0;
                    }
                }

                //verif diagonale vers haut gauche
                if(j<3 && i>2){
                    if(grille[i][j] == joueur){
                        ++cpt;
                        while(grille[i - cpt][j + cpt] == joueur){
                            ++cpt;
                        }
                        if(i != 6 && j!=0){
                            if(grille[i - cpt - 1][j + cpt + 1] != joueurAdverse || grille[i+1][j-1] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }else{
                            if(grille[i + cpt + 1][j + cpt + 1] != joueurAdverse) {
                                if (cpt == 3) {
                                    score += 1000;
                                } else if (cpt == 2) {
                                    score += 100;
                                } else {
                                    score += 10;
                                }
                            }
                        }
                        cpt = 0;
                    }else if(grille[i][j] == joueurAdverse){
                        ++cpt;
                        while(grille[i - cpt][j + cpt] == joueurAdverse){
                            ++cpt;
                        }
                        if(i != 6 && j!=0){
                            if(grille[i - cpt - 1][j + cpt + 1] != joueur || grille[i+1][j-1] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }else{
                            if(grille[i + cpt + 1][j + cpt + 1] != joueur) {
                                if (cpt == 3) {
                                    score -= 1000;
                                } else if (cpt == 2) {
                                    score -= 100;
                                } else {
                                    score -= 10;
                                }
                            }
                        }
                        cpt = 0;
                    }
                }
            }
        }
        return score;

    }
}

int Puissance_4::gameResult(int grille[7][6]){
    int cpt = 0, tmp = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            if (grille[i][j] == 0) continue;

            //verif colonne
            if(j<3){
                if(grille[i][j] != 0){
                    tmp = grille[i][j];
                    ++cpt;
                    while(grille[i][j + cpt] == tmp && cpt<4){
                        ++cpt;
                    }
                    if(cpt == 4){
                        return tmp;
                    }
                    else{
                        cpt = 0;
                    }
                }
            }

            //verif ligne
            if(i<4){
                if(grille[i][j] != 0){
                    tmp = grille[i][j];
                    ++cpt;
                    while(grille[i + cpt][j] == tmp && cpt<4){
                        ++cpt;
                    }
                    if(cpt == 4){
                        return tmp;
                    }
                    else{
                        cpt = 0;
                    }
                }
            }

            //verif diagonale vers haut droite
            if(j<3 && i<4){
                if(grille[i][j] != 0){
                    tmp = grille[i][j];
                    ++cpt;
                    while(grille[i + cpt][j + cpt] == tmp && cpt<4){
                        ++cpt;
                    }
                    if(cpt == 4){
                        return tmp;
                    }
                    else{
                        cpt = 0;
                    }
                }
            }

            //verif diagonale vers haut gauche
            if(j<3 && i>2){
                if(grille[i][j] != 0){
                    tmp = grille[i][j];
                    ++cpt;
                    while(grille[i - cpt][j + cpt] == tmp && cpt<4){
                        ++cpt;
                    }
                    if(cpt == 4){
                        return tmp;
                    }
                    else{
                        cpt = 0;
                    }
                }
            }
        }
    }
    for (int i = 0; i<7; i++) {
        for (int j = 0; j < 6; j++) {
            if (grille[i][j] == 0)return 0;
        }
    }
    return 3;
}
