
#include <stdlib.h>
#include <stdio.h>
#include "listeDouble.h"

bool AlessB (float a, float b);
bool AGreaterB (float a, float b);
bool AequalB (float a, float b);
bool compare (Tunite* a, Tunite* b, float (*get) (Tunite* unite), bool (*comp) (float a, float b));

Tunite** listeToTab (T_liste l, int* taille);
T_liste TabToList (Tunite** tab, int taille);

void swapt(Tunite* tab[], int a, int b);
int pivotQS(Tunite* tab[], int lb, int ub, float (*get) (Tunite* unite));
void quickSort(Tunite* tab[], int lb, int ub,float (*get) (Tunite* unite));
T_liste listQuickSort(T_liste l, float (*get) (Tunite* unite));
