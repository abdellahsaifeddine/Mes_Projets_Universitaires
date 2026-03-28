#ifndef TRIVIATAB_H_INCLUDED
#define TRIVIATAB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listeDouble.h"

// initialiser random mumbers system
void initRandomNbr();

//Avoir un nombre aleatoire
int getRandNbr();


//initialisation d un tableau dynamique
int* initTab(int taille);

//lire le contenu d un tableau (printf)
void readTab();



void tri_selection(int *tableau, int taille);


//Cree un eliste de n element
T_liste CreateList(int n);

//convertie une liste en tableau
int* listeToTab (T_liste l);

//convertie une liste en tableau et libere la liste
int* listeToTabFree (T_liste *l);

//convertie un tableau en liste
T_liste TabToList (int *tab, int taille);


//Trie d une liste via un tableau (Tri par selection)
void TriList (T_liste* l);

//Calcule de temps d une fonction
void chronoListe1000();












#endif // TRIVIATAB_H_INCLUDED

