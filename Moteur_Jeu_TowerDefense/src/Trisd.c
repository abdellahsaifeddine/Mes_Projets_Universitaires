#include "Trisd.h"

void tri_selection_listeATTS(T_liste* l) {
    T_liste en_cours, plus_petit, j;
    Tunite* temp;

    for (en_cours = getptrFirstCell(*l); !listeVide(en_cours); en_cours = getptrNextCell(en_cours)) {
        plus_petit = en_cours;
        for (j = getptrNextCell(en_cours); !listeVide(j); j = getptrNextCell(j)) {
            if (j->pdata->vitesseAttaque < plus_petit->pdata->vitesseAttaque) {
                plus_petit = j;
            }
        }
        // Échange des pointeurs de données
        temp = en_cours->pdata;
        en_cours->pdata = plus_petit->pdata;
        plus_petit->pdata = temp;
    }
}

void tri_selection_listeMS(T_liste* l) {
    T_liste en_cours, plus_petit, j;
    Tunite* temp;

    for (en_cours = getptrFirstCell(*l); !listeVide(en_cours); en_cours = getptrNextCell(en_cours)) {
        plus_petit = en_cours;
        for (j = getptrNextCell(en_cours); !listeVide(j); j = getptrNextCell(j)) {
            if (j->pdata->vitessedeplacement > plus_petit->pdata->vitessedeplacement) {
                plus_petit = j;
            }
        }
        // Échange des pointeurs de données
        temp = en_cours->pdata;
        en_cours->pdata = plus_petit->pdata;
        plus_petit->pdata = temp;
    }
}
