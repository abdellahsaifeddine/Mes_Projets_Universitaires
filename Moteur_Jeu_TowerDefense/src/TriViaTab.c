
#include <time.h>


#include "TriViaTab.h"
#include "listeDouble.h"


// initialiser random mumbers system
void initRandomNbr() {

    srand(time(NULL));

}

//Avoir un nombre aleatoire
int getRandNbr() {

return (rand() % 100);}



//initialisation d un tableau dynamique
int* initTab(int taille){

int* res = (int*) malloc(taille * sizeof(int));

return res;}

//lire le contenu d un tableau (printf)
void readTab(int* tab, int taille ){

for (int i = 0; i < taille; i++)
{
    printf("\n%d : %d", i + 1, tab[i]);
}
}



void tri_selection(int *tableau, int taille){

int en_cours, plus_petit, j, temp;
for (en_cours = 0; en_cours < taille - 1; en_cours++)
{
    plus_petit = en_cours;
    for (j = en_cours; j < taille; j++)
        if (tableau[j] < tableau[plus_petit])
                plus_petit = j;
            temp = tableau[en_cours];
            tableau[en_cours] = tableau[plus_petit];
            tableau[plus_petit] = temp;
            }
}




//convertie une liste en tableau et libere la liste
/*int* listeToTabFree (T_liste *l){

int taille = getNbreCell(*l);
int* tab = initTab(taille);
int i = 0;

while(*l != NULL && i < taille)
{
    tab[i] = *getPtrData(*l);
    *l = suppEnTete(*l);
    i++;
}

return tab;}

//convertie un tableau en liste
T_liste TabToList (int *tab, int taille){

T_liste l;
initListe(&l);
int i = 0;

while (taille != 0)
{
    l = ajoutEnFin(l, tab[i]);
    i++;
    taille--;
}

return l;}

//Trie d une liste via un tableau (Tri par selection)
void TriList (T_liste *l){
srand(time(NULL));
int taille = getNbreCell(*l);
int* tab = listeToTabFree(l);
tri_selection(tab, taille);
*l = TabToList(tab, taille);
}

void chronoListe1000(){

time_t depart = time(NULL);
printf("\ndep : %2.f", depart);

T_liste l;
initListe(&l);

l = CreateList(1000);

time_t med = time(NULL);

printf("\nle temps de creation d une liste de 1000 : %.2f", difftime(med, depart));
printf("\nmed : %2.f", med);

TriList(l);

time_t end = time(NULL);
printf("\nend : %2.f", end);

printf("\nTemps de tri d une liste : %.2f", difftime(end, med));

printf("\nTemps total de la fonction : %.2f", difftime(end, depart));




}
