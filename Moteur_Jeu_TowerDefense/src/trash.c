/*void combat(TListePlayer player1, TListePlayer player2){

TListePlayer range1, range2;
initListe(&range1);
initListe(&range2);

while(!listeVide(player1) && !listeVide(player2))
{
    Tunite* courant1 = getPtrData(player1);
    Tunite* courant2 = getPtrData(player2);
    TListePlayer range1 = apporteEnnemi(player2, courant1);
    TListePlayer range2 = apporteEnnemi(player1, courant2);
    printf("\n\n**************** etape 1 ******************\n");
    affichePtrPlayer(range1, "range 1 :");
    affichePtrPlayer(range2, "range 2 :");
    if(listeVide(range1) && listeVide(range2))
    {
        player1 = getptrNextCell(player1);
        player2 = getptrNextCell(player2);
        combat(player1, player2);
    }

    //tri_selection_liste(range1);
    //tri_selection_liste(range2);
    printf("\n\n**************** etape 2 ******************\n");
    affichePtrPlayer(range1, "range 1 :");
    affichePtrPlayer(range2, "range 2 :");

    while(!listeVide(range1) || !listeVide(range2))
    {
        Tunite* fighter1 = getPtrData(range1);
        Tunite* fighter2 = getPtrData(range2);

        fightEnnemi(range1, courant2);
            if(courant2->pointsDeVie <= 0)
            {supprimerUnite(player2, courant2);}
        fightEnnemi(range2, courant1);
            if(courant1->pointsDeVie <= 0)
            {supprimerUnite(player1, courant1);}

        range1 = getptrNextCell(range1);
        range2 = getptrNextCell(range2);
    }
    player1 = getptrNextCell(player1);
    player2 = getptrNextCell(player2);
}

}*/

/*//Renvoie la liste player apres que ennemi aie attaquer la liste une seule fois, supprime une unite si elle est detruite
TListePlayer fightEnnemi(TListePlayer player, Tunite* ennemi){

Tunite* fighter = getPtrData(player);

    while(!listeVide(player) && ennemi->pointsDeVie > 0)
    {
        attack(fighter, ennemi);
        sleepNanoseconds(fighter->vitesseAttaque);
        player = getptrNextCell(player);
    }
return player;}

//renvoie une liste des unites que ennemi peut attaquer depuis la liste player
TListePlayer apporteEnnemi(TListePlayer player, Tunite* ennemi){

T_liste inrange;
initListe(&inrange);
int x = ennemi->posX, y = ennemi->posY, r = ennemi->portee;


    do
    {
        Tunite* courant = getPtrData(player);
        if(inRange(courant, x, y, r))
        {
            inrange = ajoutEnFin(inrange, *courant);
        }
        player = getptrNextCell(player);
    }
    while (!listeVide(player));

return inrange;}

TListePlayer* fight(TListePlayer player1, TListePlayer* player2){

affichePtrPlayer(player1, "joueur 1 :");
affichePtrPlayer(*player2, "joueur 2 :");
TListePlayer* ennemies = player2;
Tunite* ennemi = getPtrData(*ennemies);
TListePlayer fighters = apportePlayer(player1, ennemi);
printf("*************etape 1 : data ennemi : *********\n");
        affichePtrData(ennemi);
        affichePtrPlayer(fighters, "fighters *********");

    while(listeVide(fighters))
    {
        ennemies = getptrNextCell(*ennemies);
        ennemi = getPtrData(*ennemies);
        fighters = apportePlayer(player1, ennemi);

        printf("*************etape 1.2 : data ennemi : *********\n");
        affichePtrData(ennemi);
        affichePtrPlayer(fighters, "fighters *********");

    }
printf("*******etape 2 : \n");
affichePtrPlayer(fighters, "fighters *********");
tri_selection_liste(&fighters);
affichePtrPlayer(fighters, "fighters apres tri : *******");

    while(!listeVide(fighters))
    {
        printf("*******etape 3 : ***********\n");
        attack(getPtrData(fighters), ennemi);
        if(ennemi->pointsDeVie <= 0)
        {
            supprimerUnite(&player2, ennemi);
            printf("*******etape 3.1 : \n");
            affichePtrPlayer(*player2, "joueur 2 apres suppression : ******");
            return player2;
        }
        fighters = getptrNextCell(fighters);
        printf("*******etape 3.2 : \n");
        affichePtrPlayer(fighters, "fighters: ******");
        affichePtrPlayer(*player2, "joueur 2 apres suppression : ******");
    }
 return player2;}


 void combat(TListePlayer player1, TListePlayer player2, TplateauJeu jeu){

float wait1 = 0, wait2 = 0;


        printf("\t***************** PLAYER I ATTAQUE *****************\n");
        sleepNanoseconds(wait1);
        player2 = fight(player1, player2, jeu);
        printf("\t***************** PLAYER II ATTAQUE ****************\n");
        sleepNanoseconds(wait2);
        player1 = fight(player2, player1, jeu);
}



void Pmove(TListePlayer player, TplateauJeu jeu, int Nplayer) {
    TListePlayer P = player;
    while (!listeVide(P)) {
        Tunite* unite = getPtrData(P);
        unitemove(unite, jeu, Nplayer);
        P = getptrNextCell(P);
    }
}

*/
