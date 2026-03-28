#include "clashloyal.h"
#include "tester.h"
#include "Trisd.h"
#include <stdio.h>
#include <stdlib.h>

/****************************************************************************************************************/
                /********* FONCTIONS DE CONDITIONNEMENT  DU JEU *********/
/****************************************************************************************************************/

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");
        }
        printf("\n");
    }
}

//Fonctions de creation de chacunes des unites de jeux
Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 0;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 0;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 0;
    return nouv;
}
Tunite *creeArcher (int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;
}
Tunite *creegargouille (int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 1;
    return nouv;
}
Tunite *creedragon (int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 3;
    return nouv;
}
Tunite *creechevalier (int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    if (nouv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    nouv->coutEnElixir = 4;
    return nouv;
}



// Crée un joueur avec des valeurs prédéfinies (tour et tour Roi)
TListePlayer createplayer(TListePlayer joueur, int wich) {
    if (wich == 2) {
        // Si le joueur est le joueur 2, positionne ses tours Roi et tour dans le bas du plateau
        joueur = ajoutEnTete(joueur, *creeTour(5, 15));
        joueur = ajoutEnTete(joueur, *creeTourRoi(5, 17));
    } else {
        // Si le joueur est le joueur 1, positionne ses tours Roi et tour dans le haut du plateau
        joueur = ajoutEnTete(joueur, *creeTour(5, 3));
        joueur = ajoutEnTete(joueur, *creeTourRoi(5, 1));
    }
    return joueur;
}


// Place les unités de chaque joueur sur le plateau selon leurs coordonnées
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu) {
    while (!listeVide(player)) {
        Tunite* courant = getPtrData(player); // Obtient l'unité actuelle du joueur
        int x = courant->posX;
        int y = courant->posY;

        // Vérifie si la case du plateau est libre
        if (jeu[x][y] == NULL) {
            // Si la case est vide, place l'unité sur le plateau
            jeu[x][y] = courant;
        }

        // Passe à l'unité suivante du joueur
        player = getptrNextCell(player);
    }
}


/****************************************************************************************************************/
                /********* FONCTIONS DE COMBATS *********/
/****************************************************************************************************************/

// Renvoie la liste des joueurs qui peuvent attaquer l'ennemi
TListePlayer apportePlayer(TListePlayer player, Tunite* ennemi) {
    T_liste inrange;
    initListe(&inrange); // Initialise la liste des joueurs dans la portée de l'ennemi

    // Parcours des unités du joueur
    do
    {
        Tunite* courant = getPtrData(player);
        int x = courant->posX, y = courant->posY;

        // Vérifie si l'ennemi est dans la portée de l'unité actuelle
        if (inRange(ennemi, x, y, courant->portee))
        {
            // Si l'ennemi est dans la portée, ajoute l'unité à la liste des unités dans la portée
            inrange = ajoutEnFin(inrange, *courant);
        }

        player = getptrNextCell(player);

    }
    while (!listeVide(player));

    return inrange; // Retourne la liste des joueurs dans la portée de l'ennemi
}


// Retourne une liste de joueur sans une unité détruite
TListePlayer supprimerUnite(TListePlayer player, Tunite *UniteDetruite, TplateauJeu jeu) {
    // Trouve la position de l'unité dans la liste du joueur
    int pos = findCell(player, UniteDetruite) - 1;
    // Retire l'unité du plateau de jeu
    jeu[UniteDetruite->posX][UniteDetruite->posY] = NULL;
    // Supprime l'unité de la liste du joueur
    player = suppEnN(player, pos);
    //player = suppEnTete(player);

    return player; // Retourne la liste de joueur sans l'unité détruite
}


//La premiere unite de player1 attaque toutes les unites de player2 a sa porte et supprime ceux tuees
//Retourne player2
TListePlayer fight(TListePlayer player1, TListePlayer player2, TplateauJeu jeu, bool check) {
    // Affichage des joueurs pour le débogage
    affichePtrPlayer(player1, "joueur 1 :");
    affichePtrPlayer(player2, "joueur 2 :");

    TListePlayer ennemies = player2;
    TListePlayer fighters;
    initListe(&fighters);
    Tunite* ennemi;

while(!listeVide(ennemies))
{

    // Boucle pour rechercher tous les ennemis à portée
    while(listeVide(fighters) && !listeVide(ennemies))
    {

        ennemi = getPtrData(ennemies);
        fighters = apportePlayer(player1, ennemi);
        ennemies = getptrNextCell(ennemies);

        // Affichage des informations de débogage
        printf("*************etape 1.2: *********\n");
        affichePtrData(ennemi);
        affichePtrPlayer(fighters, "fighters *********");
    }

    if(listeVide(fighters))
    {
        return player2;
    }

    // Boucle de combat
    while(!listeVide(fighters))
    {
        // Attaque du combattant sur l'ennemi
        attack(getPtrData(fighters), ennemi);
        getPtrData(fighters)->peutAttaquer = 0;

        // Si la tour de roi est détruite affiche un message
        check = checkEnd(player2);


        // Si l'ennemi est vaincu, le supprimer de la liste du joueur
        if(ennemi->pointsDeVie <= 0)
        {
            player2 = supprimerUnite(player2, ennemi, jeu);
            // Affichage pour le débogage
            printf("*******etape 3.1 : \n");
            affichePtrPlayer(player2, "joueur 2 apres suppression : ******");
            return player2;
        }

        // Passer au combattant suivant
        fighters = getptrNextCell(fighters);

        // Affichage pour le débogage
        printf("*******etape 3.2 : \n");
        affichePtrPlayer(fighters, "fighters: ******");
        affichePtrPlayer(player2, "joueur 2 apres suppression : ******");
    }
}

    // Retourner la liste du joueur 2 après le combat
return player2;}

/****************************************************************************************************************/
                    /**************** FONCTIONS DE DEPLACEMENT *************/
/****************************************************************************************************************/

//Retourne un tableau de coordonnees avec les deplacement possible pour chaque unité selon une priorité
// (N, NE, NO, E, O), no move
couple avaibleMove(Tunite* unite, TplateauJeu jeu, int Nplayer) {
    couple result[1];
    int x = unite->posX;
    int y = unite->posY;
    int count = 0, v = 1, xv = 0;

    //(V<0) pour déplacer le joueur 2 vers le haut du plateau
    if (Nplayer == 2)
    {v = -1;}

    // XV afin de se déplacer vers le centre
    if (x - (LARGEURJEU / 2) < 0)
    {xv = 1;}
    else if (x - (LARGEURJEU / 2) > 0)
    {xv = -1;}

    //faire passer tous les unites par le pont
    if((y + v) == (HAUTEURJEU/2) && jeu[LARGEURJEU/2][HAUTEURJEU/2] != NULL)
    {
        result[count].x = x;
        result[count].y = y;
        count++;
    }
    //Deplacement en diagonale vers le centre (x, y), Si l unite n 'est au centre (x)
    else if (jeu[x + xv][y + v] == NULL)
    {
        result[count].x = x + xv;
        result[count].y = y + v;
        count++;
    }

    //Deplacement en avant (y), unite deja au centre(x)
    else if (jeu[x][y + v] == NULL) {
        result[count].x = x;
        result[count].y = y + v;
        count++;
    }
    //Deplacement en avant à gauche, unite deja au centre(x) mais continuer au centre est impossible
    else if (jeu[x - 1][y + v] == NULL) {
        result[count].x = x - 1;
        result[count].y = y + v;
        count++;
    }
    //Deplacement en avant à droite, unite deja au centre(x) mais continuer au centre est impossible
    else if (jeu[x + 1][y] == NULL) {
        result[count].x = x + 1;
        result[count].y = y + v;
        count++;
    }
    //Deplacement à gauche, unite deja au centre(x) mais continuer au centre en avant est impossible
    else if (jeu[x - 1][y] == NULL) {
        result[count].x = x - 1;
        result[count].y = y;
        count++;
    }
     //Deplacement à droite, unite deja au centre(x) mais continuer au centre en avant est impossible
    else if (jeu[x + 1][y] == NULL) {
        result[count].x = x - 1;
        result[count].y = y;
        count++;
    }

    //ajouter la position actuelle de l'unité a la fin du tableau
    else
    {
        result[count].x = x;
        result[count].y = y;
        count++;
    }


    // Affichage pour debugage
    /*for(int i = 0; i < count; i++)
    {
        printf("(%d,%d)\n", result[i].x, result[i].y);
    }*/

// Retourner le tableau de couples
return *result;}

//deplace une unité dans le plateau et libère sa case précédente
void unitemove(Tunite* unite, TplateauJeu jeu, int Nplayer) {
    // Obtenez les coordonnées actuelles de l'unité
    int x = unite->posX;
    int y = unite->posY;

    // Obtenez les mouvements disponibles pour l'unité
    couple availableMoves = avaibleMove(unite, jeu, Nplayer);

    // Si l'unité n'est pas un roi ou une tour
    if (unitecode(unite->nom) != 'K' && unitecode(unite->nom) != 'T') {
        // Déplacez l'unité vers la première case disponible
        int newX = availableMoves.x;
        int newY = availableMoves.y;

        // Vérifiez si les nouvelles coordonnées sont dans les limites du plateau de jeu
        if (newX > 0 && newX < LARGEURJEU && newY > 0 && newY < HAUTEURJEU - 1) {
            // Déplacez l'unité vers la première case disponible
            //affichage pour debuggage avant
            /*printf("\n**\t");
            affichePtrData(unite);*/

            unite->posX = newX;
            unite->posY = newY;
            //affichage pour debuggage après
            /*printf("  \t");
            affichePtrData(unite);
            printf("**\n");*/
        }
    }

    // Mettre à jour le tableau de jeu après le déplacement de l'unité
    jeu[x][y] = NULL;
    jeu[unite->posX][unite->posY] = unite;
}

// déplace les deux joueurs selon la vitesse de déplacement de chaque unité
void moove(TListePlayer player1, TListePlayer player2, TplateauJeu jeu) {

    TListePlayer joueur1 = player1;
    TListePlayer joueur2 = player2;

    // Trier les copies des listes des joueurs en fonction de la vitesse de déplacement de l'unité
    //tri_selection_listeMS(&joueur1);
    //tri_selection_listeMS(&joueur2);

    // Boucler à travers chaque joueur tant que les deux listes ne sont pas vides
    while (!listeVide(joueur1) && !listeVide(joueur2))
    {
        // Obtenez l'unité en cours de traitement pour chaque joueur
        Tunite* unite1 = getPtrData(joueur1);
        Tunite* unite2 = getPtrData(joueur2);

        // Effectuez le mouvement de l'unité la plus rapide
        if (unite1->vitessedeplacement > unite2->vitessedeplacement)
        {
            if(unite1->peutAttaquer == 1)
            {
                unitemove(unite1, jeu, 1);
                joueur1 = getptrNextCell(joueur1);
            }

        }
        else
        {
            if(unite2->peutAttaquer == 1)
            {
                unitemove(unite2, jeu, 2);
                joueur2 = getptrNextCell(joueur2);
            }
        }

        //unite1->peutAttaquer = 1;
        //unite2->peutAttaquer = 1;
    }


    // Déplacez les unités restantes si l'une des listes est vide
    while (!listeVide(joueur1))
    {
        Tunite* unite1 = getPtrData(joueur1);
        unitemove(unite1, jeu, 1);
        //unite1->peutAttaquer = 1;
        joueur1 = getptrNextCell(joueur1);
    }


    while (!listeVide(joueur2))
    {
        Tunite* unite2 = getPtrData(joueur2);
        unitemove(unite2, jeu, 2);
        //unite2->peutAttaquer = 1;
        joueur2 = getptrNextCell(joueur2);
    }
}

/****************************************************************************************************************/
                /**************** FONCTIONS D ACHAT *************/
/****************************************************************************************************************/

// Un tableau avec les 4 unités avec leurs positions de départ trié selon le cout d elexir
Tunite** possibleUnit(int player) {
    Tunite** units = malloc(4 * sizeof(Tunite*)); // Alloue de la mémoire pour 4 unites

    if (units == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Initialise le tableau de pointeurs
    for (int i = 0; i < 4; i++) {
        units[i] = malloc(sizeof(Tunite));
        if (units[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
    }

    if (player == 2) {
        *units[0] = *creegargouille(3, 15);
        *units[1] = *creeArcher(4, 15);
        *units[2] = *creedragon(7, 15);
        *units[3] = *creechevalier(6, 15);
    } else {
        *units[0] = *creegargouille(3, 3);
        *units[1] = *creeArcher(4, 3);
        *units[2] = *creedragon(7, 3);
        *units[3] = *creechevalier(6, 3);
    }

    return units;
}

//choisie du tableau units, une unité entre 0 et var-1
Tunite* chooseRandUnit(Tunite** units, int var) {
    return units[randm(var)];
}

//choisie une unité de units selon le cout d elexir disponible
Tunite* chooseUnit(Tunite** units, int myElixir) {
    if (myElixir <= 0) {
        return NULL; // Aucun achat possible avec 0 ou moins d'élixir
    } else if (myElixir == 1) {
        return units[0];
    } else if (myElixir <= 2) {
        return chooseRandUnit(units, 2);
    } else if (myElixir <= 3) {
        return chooseRandUnit(units, 3);
    } else {
        // Si j'ai plus de 3 élixirs, je peux toujours acheter une des 4 unités
        return chooseRandUnit(units, 4);
    }
}

//definie une unité et supprime son cout de myelixir
Tunite* AcheteUnite(int *myElixir, int player) {
    Tunite** possibleUnite = possibleUnit(player);
    Tunite* newUnit;
    if(*myElixir > 0)
    {
        newUnit = chooseUnit(possibleUnite, *myElixir);
        *myElixir -= newUnit->coutEnElixir;
        // Libérer la mémoire allouée pour les pointeurs de Tunite
        for (int i = 0; i < 4; i++)
        {
            free(possibleUnite[i]);
        }
    free(possibleUnite);
    }
    else{return NULL;}
return newUnit;}

//ajoute nouvelleUnite a player
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){

if(!listeVide(*player) && nouvelleUnite != NULL)
{
    *player = ajoutEnN(*player, 1, *nouvelleUnite);

}
}

/****************************************************************************************************************/
                /**************** END GAME *************/
/****************************************************************************************************************/



// Vérifie si la tour Roi d'un joueur est détruite
// Renvoie true si elle est détruite, sinon false
bool tourRoiDetruite(TListePlayer player1) {
    Tunite* kingTower = getPtrSelectData(player1, tourRoi); // Obtient la tour Roi du joueur

    // Vérifie si les points de vie de la tour Roi sont inférieurs ou égaux à zéro
    return (kingTower->pointsDeVie <= 0);

    /*if(getPtrData(player1)->nom != tourRoi)
    {return true;}*/
 //return false;
 }

bool checkEnd(TListePlayer p1){

    int wich = 0;
        if((getPtrData(p1))->posY == 1)
            {wich = 1;}
        else
            {wich = 2;}
        if(tourRoiDetruite(p1))
        {
            message("The end", "The Tower King FALL", wich);
            printf("The Tower King FALL, player %d WIN", wich);
            return true;
        }


return false;}

TListePlayer resetAttack(TListePlayer player){

    TListePlayer p = player;


    while(!listeVide(p))
    {
        Tunite* unite = getPtrData(p);
        unite->peutAttaquer = 1;
        p = getptrNextCell(p);
    }

return player;}



