Puissance 4
==

**Projet réalisé dans le cadre du module d'intelligence artificielle pour un master Ingenierie Informatique et Innovation**


####  Compilation et execution

    g++ -std=c++11 -Wall -Werror -o pui4 *.cpp
    ./pui4
    
#### Règles du puissance 4

Le jeu se déroule sur une grille de 42 cases (7 colonnes de hauteur 6). Tour par tour, les joueurs choisissent une colonne où ils vont déposer leur jeton. Le premier joueur qui aligne 4 jetons a gagné.

####  Modes de jeux 

* Jouer à deux joueurs : mode de jeu classique 
* Jouer contre l'IA (Facile) : Jouer contre une IA qui joue aléatoirement
* Jouer contre l'IA (Moyen) : Jouer contre une IA qui implémente un algorithme negamax de profondeur 4
* Jouer contre l'IA (Difficile) : Jouer contre une IA qui implémente un algorithme negamax de profondeur 8
* Mode spectateur : Regarder deux IA qui implémentent un algorithme de profondeur 8 s'affronter

#### Fonctionnement Puissance 4 

Les joueurs jouent chacun leur tour tant que l'un d'eux n'a pas gagné ou que 42 ont été joués.
Pour faciliter la compréhension du code, la grille est modélisée par un simple tableau d'entier à 2 dimensions contenant 3 valeurs : 0 si aucun coup n'a été joué, le numéro du joueur qui a joué à cette case (1 ou 2)
Pour l'affichage et la vérification de victoire, le tableau est lu à l'envers pour simuler une grille de puissance 4.

    for (int row = 5; row >= 0; row--) {
        for (int col = 0; col < 7; col++) {
            // Code
        }
    }
    
#### Implémentation de l'intelligence artificelle 

L'intelligence artificielle est implémentée avec l'algorithme Negamax optimisé par un élagage Alpha-Beta.
L'algorithme Negamax est une simplification de l'algorithme Min Max.
Au lieu de minimiser les coups du joueur et maximiser les coups adverses. L'algorithme Negamax va simplement maximiser l'opposé du prochain coup simulé.


```

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
        std::array<int, 7> columns {{3, 4, 5, 0, 1, 2, 6}};
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
```

La fonction d'évalution va définir un score en fonction des conditions suivantes :

>Si le joueur gagne : 10000 - nombre de coups simulés  
Si le joueur adverse gagne : -10000 + nmbre de coups simulés  
Sinon on compte le nombre d'alignements de 1, 2 ou 3 jetons encore "jouables" (C'est à dire qu'il est toujours possible d'aligner un nouveau jeton à la suite)  
10 pour un jeton jouable, 100 pour une série de deux jetons jouables et 1000 points pour une série de 3 jetons jouables