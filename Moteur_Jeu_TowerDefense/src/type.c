#include "type.h"
#include <time.h>
#include <stdlib.h>


// Recupere la vitesse d attaque d une unite depuis un tableau
float getATTS(Tunite* unite){

return unite->vitesseAttaque;}

// Recupere la vitesse de deplacement d une unite depuis un tableau
float getMS(Tunite* unite){

return unite->vitessedeplacement;}


// Nomme les unités du jeu data selon l'initiale de chaque unité
char unitecode(TuniteDuJeu data) {
    switch (data) {
        case tour:
            return 'T';
        case tourRoi:
            return 'K';
        case archer:
            return 'A';
        case chevalier:
            return 'C';
        case dragon:
            return 'D';
        case gargouille:
            return 'G';
    }
return 'N';} // Retourne 'N' si l'unité n'est pas reconnue

// Teste si les coordonnées de l'unité sont dans le cercle de centre (x, y) et de rayon r
bool inRange(Tunite* unite, int x, int y, int r) {
    int a = unite->posX, b = unite->posY;
    int point = pow(x - a, 2) + pow(y - b, 2);
    int rayon = pow(r, 2);

    if (point <= rayon)
    {
        return true;
    }

return false;}

// L'unité combattante attaque l'ennemi et réduit ses points de vie des dégâts de l'attaquant
void attack(Tunite* fighter, Tunite* ennemi) {
    if (fighter->peutAttaquer == 1)
    {
        if (fighter->cibleAttaquable == solEtAir || fighter->cibleAttaquable == ennemi->maposition)
        {
            ennemi->pointsDeVie -= fighter->degats;
            //fighter->peutAttaquer = 0; // Empêche l'attaquant d'attaquer à nouveau
        }
    }
}

// Convertit la vitesse d'attaque en une durée à attendre en nanosecondes
long convertToNanoseconds(float attackSpeed) {
    // Convertit la vitesse d'attaque en millisecondes
    long milliseconds = (long)(attackSpeed * 1000);

    // Convertit les millisecondes en nanosecondes
    return milliseconds * 1000000L;
}

// Attend pendant une durée spécifiée en nanosecondes
void sleepNanoseconds(float attackSpeed) {
    long nanoseconds = convertToNanoseconds(attackSpeed);
    struct timespec sleepTime, remainingTime;

    // Convertit la durée en structure timespec
    sleepTime.tv_sec = nanoseconds / 1000000000;
    sleepTime.tv_nsec = nanoseconds % 1000000000;

    // Attend la durée spécifiée
    nanosleep(&sleepTime, &remainingTime);
}

// Génère un nombre aléatoire entre 0 et var - 1
int randm(int var) {
return rand() % var;}
