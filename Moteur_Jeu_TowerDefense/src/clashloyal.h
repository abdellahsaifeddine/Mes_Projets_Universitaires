#ifndef JEU2048_H_INCLUDED
#define JEU2048_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19
#include "listeDouble.h"


typedef T_liste TListePlayer;

typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);


TListePlayer createplayer(TListePlayer joueur, int wich);

Tunite *creeTour(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeArcher (int posx, int posy);
Tunite *creegargouille (int posx, int posy);
Tunite *creedragon (int posx, int posy);


void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);


TListePlayer apporteEnnemi(TListePlayer player, Tunite *ennemi);
TListePlayer apportePlayer(TListePlayer player, Tunite* ennemi);
TListePlayer fight(TListePlayer player1, TListePlayer player2, TplateauJeu jeu, bool check);
TListePlayer supprimerUnite(TListePlayer player, Tunite *UniteDetruite, TplateauJeu jeu);
TListePlayer fightEnnemi(TListePlayer player, Tunite* ennemi);

void combat(TListePlayer player1, TListePlayer player2, TplateauJeu jeu);


couple avaibleMove(Tunite* unite, TplateauJeu jeu, int Nplayer);
void unitemove(Tunite* unite, TplateauJeu jeu, int Nplayer);
void Pmove(TListePlayer player, TplateauJeu jeu, int Nplayer);
void moove(TListePlayer player1, TListePlayer player2, TplateauJeu jeu);



Tunite** possibleUnit(int player);
Tunite* chooseRandUnit(Tunite** units, int var);
Tunite* chooseUnit(Tunite** units, int myElixir);
Tunite* AcheteUnite(int *myElixir, int player);
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);


bool tourRoiDetruite(TListePlayer player);
bool checkEnd(TListePlayer p1);
TListePlayer resetAttack(TListePlayer player);



#endif // JEU2048_H_INCLUDED
