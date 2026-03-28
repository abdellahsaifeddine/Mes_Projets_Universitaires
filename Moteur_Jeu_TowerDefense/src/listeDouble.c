#include <stdio.h>
#include <stdlib.h>


#include "listeDouble.h"


void initListe(T_liste *l){
*l=NULL;
}

bool listeVide( T_liste l){
    return (l==NULL);
}
bool dataVide( T_liste l){
    return (l->pdata==NULL);
}

void afficheListeV1 (T_liste l){

T_liste courant = l;

if (listeVide(courant))
    printf("liste vide");

while(courant != NULL)
{
    printf("%d", (courant->pdata->nom));
    courant = courant->suiv;
}
}

//Fonction d'ajout (en tete, a la fin, et en nieme position)
T_liste ajoutEnTete(T_liste l, Tunite mydata){

T_liste mylist = (T_liste)(malloc(sizeof(T_cellule)));
mylist->pdata= (Tunite*)malloc(sizeof(Tunite));

*(mylist->pdata) = mydata;
mylist->suiv = l;
mylist->prec = NULL;
if (l != NULL)
{l->prec = mylist; }

return mylist;}

T_liste ajoutEnFin(T_liste l, Tunite mydata){

T_liste mylist = (T_liste)(malloc(sizeof(T_cellule)));
mylist->pdata = (Tunite*) malloc(sizeof(Tunite));

*(mylist->pdata) = mydata;
mylist->suiv = NULL;
mylist->prec = l;
if(l == NULL)
{return mylist;}
T_liste courant = l;
while(courant->suiv != NULL)
{
courant = courant->suiv;
}
courant->suiv = mylist;
mylist->prec = courant;


return l;}

T_liste ajoutEnN(T_liste l, int pos, Tunite mydata){

T_liste mylist = (T_liste)malloc(sizeof(T_cellule));
mylist->pdata = (Tunite*)malloc(sizeof(Tunite));

*(mylist->pdata) = mydata;
mylist->prec = NULL;
mylist->suiv = NULL;

if(listeVide(l))
{afficheListeV1(l);}

T_liste courant = l;
int count = 0;

while(courant->suiv != NULL && count < pos - 1)
{
count++;
courant = courant->suiv;
}
if (count == pos - 1)
{
mylist->suiv = courant->suiv;
mylist->prec = courant;
courant->suiv = mylist;
}

else
printf("la liste ne contient que %d element\n", count+1);



return l;}



 //Fonction de supression (en tete, a la fin, et en nieme position)
T_liste suppEnTete(T_liste l){

if(listeVide(l))
{return NULL;}


T_liste mylist = l->suiv;

free(l->pdata);
free(l);

return mylist;}

T_liste suppEnFin(T_liste l){

if(listeVide(l))
{return NULL;}

if(l->suiv == NULL)
{
    free(l->pdata);
    free(l);
return NULL;}

T_liste courant = l;
T_liste suivant = l->suiv;

while(suivant->suiv != NULL)
{
courant = suivant;
suivant = suivant->suiv;
}

free(suivant->pdata);
free(suivant);
courant->suiv = NULL;


return l;}

T_liste suppEnN(T_liste l, int pos){

if(listeVide(l))
{
    return NULL;
}

if(pos == 0)
{
return suppEnTete(l);
}

int count = 0;

T_liste courant = l;

while(courant->suiv != NULL && count < pos - 1)
{
    courant = courant->suiv;
    count++;
}

if (courant->suiv == NULL )
{
    return l;
}

else
{
    T_liste target = courant->suiv;
    courant->suiv = target->suiv;
    target->prec = courant;
    free(target->pdata);
    free(target);
}

return l;}




//Fonction de pointeur sur (tete, fin, et  nieme position)
T_liste getptrFirstCell(T_liste l){

if (listeVide(l))
    {
       return NULL;
    }

T_cellule* ptr = l;
//printf("\nla data First est : %d", *(ptr->pdata));

return ptr;}

T_liste getptrLastCell(T_liste l){

if(listeVide(l))
    {
        return NULL;
    }

T_cellule* ptr = l;

while(ptr->suiv != NULL)
{
    ptr = ptr->suiv;
}
//printf("\nla data Last : %d", *(ptr->pdata));

return ptr;}

T_liste getptrNextCell(T_liste l){

if(listeVide(l))
{
    return NULL;
}

T_cellule* ptr = l;

if(ptr == NULL)
{
//printf("\npas de suivant");
return NULL;
}

else
{
ptr = ptr->suiv;
}

//printf("\nla data Next : %d", *(ptr->pdata));

return ptr;}

T_liste getptrPrevCell(T_liste l){

if(listeVide(l))
{
    NULL;
}

T_cellule* ptr = l;

if(ptr->prec == NULL)
{
    printf("\naucun precedent");
return NULL;}


ptr = ptr->prec;


//printf("\nla data Prev : %d", *(ptr->pdata));

return ptr;}

Tunite* getPtrData(T_liste l){

if (listeVide(l))
{
   return NULL;
}

return getptrFirstCell(l)->pdata;}



  //retourne pointeur d une data donnee si elle existe dans la liste
Tunite* getPtrSelectData(T_liste l, TuniteDuJeu mydata) {

    if (listeVide(l))
    {
        return NULL;
    }

    while (!listeVide(l) && mydata != getPtrData(l)->nom)
    {
        l = getptrNextCell(l);
    }

    if (listeVide(l))
    {
        printf("Data not found\n");
        return NULL;
    }

return getPtrData(l);}

//nombre de cellule d une liste
int getNbreCell(T_liste l){

if(listeVide(l))
{
afficheListeV1(l);
return 0;}

int nbr = 0;

while(l->suiv != NULL)
{
l = l->suiv;
nbr++;
}

return nbr + 1;}

//la taille en bytes d une liste
int getSizeBytes(T_liste l){

int size = sizeof(T_cellule);

return  size * getNbreCell(l);}




  //fusionne 2 listes dans une nouvelle liste
T_liste creatNewListeFromFusion(T_liste l1, T_liste l2){

T_liste newliste;
initListe(&newliste);

if (listeVide(l1))
{return l2;}

else if (listeVide(l2))
{return l1;}

else
{
    T_liste courant1 = l1;
    T_liste courant2 = l2;

        while(courant1 != NULL && courant2 != NULL)
        {
            newliste = ajoutEnFin(newliste, *(getptrFirstCell(courant1)->pdata));
            courant1 = courant1->suiv;
            newliste = ajoutEnFin(newliste, *(getptrFirstCell(courant2)->pdata));
            courant2 = courant2->suiv;
        }

        while(courant1 != NULL)
        {
            newliste = ajoutEnFin(newliste, *(getptrFirstCell(courant1)->pdata));
            courant1 = courant1->suiv;
        }

        while(courant2 != NULL)
        {
            newliste = ajoutEnFin(newliste, *(getptrFirstCell(courant2)->pdata));
            courant2 = courant2->suiv;
        }

}

return newliste;}

 //Concatenation de deux liste
T_liste addBehind(T_liste debut, T_liste suite){

if (listeVide(debut))
{return suite;}

else if (listeVide(suite))
{return debut;}

else
{
    while(suite != NULL)
    {
        ajoutEnFin(debut, *(suite->pdata));
        suite = suite->suiv;
    }
}

return debut;}


//recherche du pointeur d une cellule si sa valeur dans la liste
int findCell(T_liste l, Tunite* data){

if(listeVide(l))
{return -1;}

T_liste ptr = l;
int pos = 1;

while(!listeVide(ptr))
{

    if(getPtrData(ptr) == data)
    {
        return pos;
    }
    else
    {
        ptr = ptr->suiv;
        pos++;
    }
}


return 0;}

