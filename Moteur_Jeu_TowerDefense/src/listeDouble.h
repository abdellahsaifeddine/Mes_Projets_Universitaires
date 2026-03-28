#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>
#include <string.h>
#include "type.h"


typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tunite *pdata;
} T_cellule;

typedef T_cellule *T_liste;


void initListe(T_liste *l);

bool listeVide( T_liste l);

void afficheListeV1( T_liste l);



T_liste ajoutEnTete(T_liste l, Tunite mydata);

T_liste ajoutEnFin(T_liste l, Tunite mydata);

T_liste ajoutEnN(T_liste l, int pos, Tunite mydata);




T_liste suppEnTete(T_liste l);

T_liste suppEnFin(T_liste l);

T_liste suppEnN(T_liste l, int pos);



T_liste getliste(int dep, int fin);



T_liste getptrFirstCell(T_liste l);

T_liste getptrLastCell(T_liste l);

T_liste getptrNextCell(T_liste l);

T_liste getptrNextCellB(T_liste l);

T_liste getptrPrevCell(T_liste l);

Tunite* getPtrData(T_liste l);


Tunite* getPtrSelectData(T_liste l, TuniteDuJeu mydata);

void swapPtrData( T_liste source, T_liste destination );

int getSizeBytes(T_liste l);



T_liste creatNewListeFromFusion(T_liste l1, T_liste l2);
T_liste addBehind(T_liste debut, T_liste suite);



int findCell(T_liste l, Tunite* data);



int getOccurences(T_liste l, Tunite data);


void afficheListeV2( T_liste l);


#endif

