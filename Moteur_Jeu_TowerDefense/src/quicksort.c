#include "quicsort.h"


// Compare A et B, retourne true si A < B
bool AlessB (float a, float b){
return a < b;}

// Compare A et B, retourne true si A > B
bool AGreaterB (float a, float b){
return a > b;}

// Compare A et B, retourne true si A = B
bool AequalB (float a, float b){
return a == b;}

// Compare deux unités (comp), selon leurs ATTS/MS (get)
bool compare (Tunite* a, Tunite* b, float (*get) (Tunite* unite), bool (*comp) (float a, float b)){

float A = get(a);
float B = get(b);

return comp(A, B);}



// Convertie une liste en tableau
Tunite** listeToTab (T_liste l, int* taille){

if (listeVide(l))
{return NULL;}

Tunite** tab = malloc(*taille * sizeof(Tunite*));

while(l != NULL)
{
    tab[*taille - 1] = getPtrData(l);
    (*taille)++;
    tab = realloc(tab, *taille * sizeof(Tunite*));
    l = getptrNextCell(l);
}

return tab;}

// Convertie un tableau en liste
T_liste TabToListe(Tunite** tab, int taille){

    T_liste l;
    initListe(&l);
    Tunite king;

    for (int i = 0; i < taille; i++)
    {
        if (unitecode(tab[i]->nom) == 'K')
        {
            king = *tab[i];
        }

        else
        {
            l = ajoutEnTete(l, (*tab[i]));
        }
        free(tab[i]);
    }
    l = ajoutEnTete(l, king);
    free(tab);

return l;}



// Swap T[a] avec T[b]
void swapt(Tunite* tab[], int a, int b){

Tunite* temp = tab[a];
tab[a] = tab[b];
tab[b] = temp;

}

// Tri le premier element du tableau (ascendant), methode pivot, et retourne sa nouvelle position
int pivotQS(Tunite* tab[], int lb, int ub, float (*get) (Tunite* unite)){

    Tunite* pivot = tab[lb];
    int start = lb + 1, end = ub;

    while (start <= end)
    {
        if (get == getATTS) // POUR A
        {
            while (start <= ub && (compare(tab[start], pivot, get, AGreaterB) || compare(tab[start], pivot, get, AequalB)))
                {start++;}
            while (end > lb && compare(tab[end], pivot, get, AlessB))
                {end--;}
        }
        else if (get == getMS)
        { // POUR ATTS
            while (start <= ub && (compare(tab[start], pivot, get, AlessB) || compare(tab[start], pivot, get, AequalB)))
                {start++;}
            while (end > lb && compare(tab[end], pivot, get, AGreaterB))
                {end--;}
        }

        if (start < end)
            {swapt(tab, start, end);}
    }
    swapt(tab, lb, end);

return end;}


// Tri rapide avec pivot
void quickSort(Tunite* tab[], int lb, int ub, float (*get) (Tunite* unite)){

    if (lb < ub)
    {
    int pivot = pivotQS(tab, lb, ub, get);
        if (pivot - 1 > lb)
            {quickSort(tab, lb, pivot - 1, get);}
        if (pivot + 1 < ub)
            {quickSort(tab, pivot + 1, ub, get);}
    }
}


T_liste listQuickSort(T_liste l, float (*get) (Tunite* unite)){

T_liste result;
initListe(&result);
int count = 1;
Tunite** tab = listeToTab(l, &count);
quickSort(tab, 0, count - 2, get);
result = TabToListe(tab, count - 1);
return result;}



