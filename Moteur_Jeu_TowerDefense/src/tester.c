#include "tester.h"

// Fonction pour afficher les informations d'une unité spécifique
void affichePtrData(Tunite* data) {
    // Affichage du nom, des coordonnées (x, y) et des points de vie de l'unité
    printf("Nom : %c (x = %d, y = %d), Points de vie : %d : ", unitecode(data->nom), data->posX, data->posY, data->pointsDeVie);
    // Affichage de la vitesse d'attaque et de l'adresse mémoire de l'unité
    printf("ATTS: %.2f  MS: %.2f  %p\n", data->vitesseAttaque, data->vitessedeplacement, (void *)data);
}

// Fonction pour afficher une liste de pointeurs vers des unités de joueur
void affichePtrPlayer(TListePlayer P, char wich[]) {
    // Affichage du nom du joueur
    printf("Liste de pointeurs d unites %s :\n", wich);
    int count1 = 1;
    TListePlayer l = P;
    // Parcours de la liste et affichage de chaque unité
    while (!listeVide(l)) {
        printf("Unite %d : ", count1);
        // Utilisation de la fonction affichePtrData pour afficher les informations de l'unité
        affichePtrData(getPtrData(l));
        count1++;
        l = getptrNextCell(l);
    }
    printf("\n");
}

// Fonction pour afficher uniquement le nom d'une unité spécifique
void affichePtrDataName(Tunite* data) {
    // Affichage du nom de l'unité
    printf("Pointeur sur les donnees %c \n", unitecode(data->nom));
}
